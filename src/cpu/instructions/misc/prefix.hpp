#pragma once

#include "instruction.hpp"

class PREFIX : public Instruction
{
    public:
        int GetInstructionLength() { return 1; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            //set prefix flag in cpu state
            cpuState->InstructionPrefix = true;

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }    
};
