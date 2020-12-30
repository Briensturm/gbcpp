#pragma once

#include "instruction.hpp"

class STOP : public Instruction
{
    public:
        int GetInstructionLength() { return 1; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            cpuState->StopMode = true;

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }    
};
