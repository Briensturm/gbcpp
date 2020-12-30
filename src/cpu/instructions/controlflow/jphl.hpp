#pragma once

#include "instruction.hpp"

class JPHL : public Instruction
{
    public:
        int GetInstructionLength() { return 1; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            cpuState->ProgramCounter = cpuState->Registers->HL;

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }
};
