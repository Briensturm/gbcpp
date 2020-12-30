#pragma once

#include "instruction.hpp"

class NOP : public Instruction
{
        public:
        int GetInstructionLength() { return 1; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            Instruction::ExecuteCycle(cpuState, mainMemory);
        }    
};
