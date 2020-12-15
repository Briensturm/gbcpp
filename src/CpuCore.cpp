#include "CpuCore.hpp"

CpuCore::CpuCore(RamPtr mainMemory, CpuStatePtr cpuState)
{
    /*_mainMemory = mainMemory;
    _cpuState = cpuState;

    _instructionDecoder = new InstructionDecoder();

    _logger = logger;

    Reset();*/
}


        /*private IInstruction CurrentInstruction
        {
            get
            {
                if (_currentInstruction == null)
                    _currentInstruction = GetNextInstruction();

                return _currentInstruction;
            }

            set => _currentInstruction = value;
        }*/

void CpuCore::AdvanceMachineCycle()
{   
    /*     
    //execute one cycle of the instruction, if not in halt/stop
    if(IsCpuRunning)
        CurrentInstruction.ExecuteCycle(_cpuState, _mainMemory);            

    if (CurrentInstruction.IsFetchNecessary())
    {
        //check for interrupts
        var readyInterrupts = GetRequestedAndEnabledInterrupts();
        if(readyInterrupts != 0 && !_cpuState.InstructionPrefix)
        {
            _cpuState.HaltMode = false;
            _cpuState.StopMode = false;

            if (_cpuState.InterruptMasterEnable)
                CurrentInstruction = _instructionDecoder.GetInterruptServiceRoutineInstruction(readyInterrupts);
            else
                CurrentInstruction = GetNextInstruction();
        }

        else if (IsCpuRunning)
            CurrentInstruction = GetNextInstruction();
    }                

    //delayed EI handling
    if(_cpuState.ImeScheduled)
    {
        _cpuState.ImeScheduled = false;
        _cpuState.InterruptMasterEnable = true;
    }*/
}

void CpuCore::Reset()
{
    /*_cpuState.Reset();
    CurrentInstruction = null;*/
}

std::shared_ptr<IInstruction> CpuCore::GetNextInstruction()
{
    /*auto nextOpcode = _mainMemory.ReadByte(_cpuState.ProgramCounter++);            

    if (_cpuState.InstructionPrefix)
    {
        _cpuState.InstructionPrefix = false;
        return _instructionDecoder.DecodeInstruction(nextOpcode, true);
    }

    if (_cpuState.HaltBug)
    {
        _cpuState.ProgramCounter--;
        _cpuState.HaltBug = false;
    }

    return _instructionDecoder.DecodeInstruction(nextOpcode);    */

    return nullptr;
}

uint8_t CpuCore::GetRequestedAndEnabledInterrupts()
{
    /*auto interruptFlags = _mainMemory.ReadByte(MiscRegisters.InterruptFlags) & 0x1F;
    if (interruptFlags == 0)
        return 0;

    auto interruptEnable = _mainMemory.ReadByte(MiscRegisters.InterruptEnable);            

    return (uint8_t)(interruptEnable & interruptFlags);*/

    return 0;
}

bool CpuCore::IsCpuRunning()
{
    return !_cpuState->StopMode && !_cpuState->HaltMode;
}