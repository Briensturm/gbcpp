#pragma once

#include "instruction.hpp"

class EI : public Instruction
{
    public:
        int GetInstructionLength() { return 1; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            cpuState->ImeScheduled = true;

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }    
};
