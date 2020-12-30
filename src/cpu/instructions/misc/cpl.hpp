#pragma once

#include "instruction.hpp"

class CPL : public Instruction
{
    public:
        int GetInstructionLength() { return 1; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            cpuState->Registers->A = (byte)~cpuState->Registers->A;

            cpuState->Registers->SubtractionFlag = true;
            cpuState->Registers->HalfCarryFlag = true;

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }
};
