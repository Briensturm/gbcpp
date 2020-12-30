#pragma once

#include "instruction.hpp"

class DECR8 : public Instruction
{
    public:
        int GetInstructionLength() { return 1; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            auto registerIndex = _opcode >> 3;
            auto oldValue = cpuState->Registers->ReadRegister(registerIndex);
            cpuState->Registers->WriteRegister(registerIndex, oldValue-1);

            cpuState->Registers->SubtractionFlag = true;
            cpuState->Registers->ZeroFlag = cpuState->Registers->ReadRegister(registerIndex) == 0;
            cpuState->Registers->HalfCarryFlag = (oldValue & 0x0F) == 0;

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }
};
