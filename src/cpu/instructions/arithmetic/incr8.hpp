#pragma once

#include "instruction.hpp"

class INCR8 : public Instruction
{
    public:
        int GetInstructionLength() { return 1; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            auto registerIndex = _opcode >> 3;
            cpuState->Registers->WriteRegister(registerIndex, cpuState->Registers->ReadRegister(registerIndex) +1);

            cpuState->Registers->SubtractionFlag = false;
            cpuState->Registers->ZeroFlag = cpuState->Registers->ReadRegister(registerIndex) == 0;
            cpuState->Registers->HalfCarryFlag = (cpuState->Registers->ReadRegister(registerIndex) & 0x0F) == 0;

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }
};
