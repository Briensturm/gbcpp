#include "instruction.hpp"

#include <stdexcept>

void IInstruction::ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
{
    if (cpuState == nullptr)
        throw std::invalid_argument("cpuState must not be nullptr.");
    if (mainMemory == nullptr)
        throw std::invalid_argument("mainMemory must not be nullptr.");

    //caller needs to check IsFetchNecessary() beforehand
    if (IsFetchNecessary())
        throw std::logic_error("No remaining cycles for this instruction");

    _remainingCycles--;
}

bool IInstruction::IsFetchNecessary()
{
    return _remainingCycles == 0;
}

void IInstruction::Initialize(uint8_t opcode = 0x00)
{
    _remainingCycles = GetInstructionLength();
    _opcode = opcode;
}

bool IInstruction::IsConditionMet(const CpuStatePtr& cpuState)
{
    auto condition = _opcode & 0x18;
    auto registers = *cpuState->Registers;

    switch(condition)
    {
        case 0x00:
            return !registers.ZeroFlag;
            break;
        case 0x08:
            return registers.ZeroFlag;
            break;
        case 0x10:
            return !registers.CarryFlag;
            break;
        case 0x18:
            return registers.CarryFlag;
            break;
        default:
            throw std::logic_error("Unexpected behavior for conditional opcode.");
    };
}