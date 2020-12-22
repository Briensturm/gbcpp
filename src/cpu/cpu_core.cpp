#include "cpu_core.hpp"

using namespace constants;

void CpuCore::AdvanceMachineCycle()
{     
    //execute one cycle of the instruction, if not in halt/stop
    if(IsCpuRunning())
        GetCurrentInstruction()->ExecuteCycle(_cpuState, _ram);            

    if (GetCurrentInstruction()->IsFetchNecessary())
    {
        //check for interrupts
        auto readyInterrupts = GetRequestedAndEnabledInterrupts();
        if(readyInterrupts != 0 && !_cpuState->InstructionPrefix)
        {
            _cpuState->HaltMode = false;
            _cpuState->StopMode = false;

            if (_cpuState->InterruptMasterEnable)
                _currentInstruction = _instrDecoder->GetInterruptServiceRoutineInstruction(readyInterrupts);
            else
                _currentInstruction = GetNextInstruction();
        }

        else if (IsCpuRunning())
            _currentInstruction = GetNextInstruction();
    }                

    //delayed EI handling
    if(_cpuState->ImeScheduled)
    {
        _cpuState->ImeScheduled = false;
        _cpuState->InterruptMasterEnable = true;
    }
}

void CpuCore::Reset()
{
    _cpuState->Reset();
    _currentInstruction = nullptr;
}

InstrPtr CpuCore::GetNextInstruction()
{
    auto nextOpcode = _ram->ReadByte(_cpuState->ProgramCounter++);            

    if (_cpuState->InstructionPrefix)
    {
        _cpuState->InstructionPrefix = false;
        return _instrDecoder->DecodePrefixedInstruction(nextOpcode);
    }

    if (_cpuState->HaltBug)
    {
        _cpuState->ProgramCounter--;
        _cpuState->HaltBug = false;
    }

    return _instrDecoder->DecodeInstruction(nextOpcode);
}

byte CpuCore::GetRequestedAndEnabledInterrupts() const
{
    auto interruptFlags = _ram->ReadByte(reg::int_flags) & 0x1F;
    if (interruptFlags == 0)
        return 0;

    auto interruptEnable = _ram->ReadByte(reg::int_enable);            

    return (byte)(interruptEnable & interruptFlags);
}

bool CpuCore::IsCpuRunning() const
{
    return !_cpuState->StopMode && !_cpuState->HaltMode;
}

InstrPtr CpuCore::GetCurrentInstruction()
{
    if (_currentInstruction == nullptr)
        _currentInstruction = GetNextInstruction();

    return _currentInstruction;
}