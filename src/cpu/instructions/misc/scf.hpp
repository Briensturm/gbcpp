#pragma once

#include "instruction.hpp"

class SCF : public Instruction
{
    public:
        int GetInstructionLength() { return 1; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            cpuState->Registers->CarryFlag = true;
            cpuState->Registers->HalfCarryFlag = false;
            cpuState->Registers->SubtractionFlag = false;

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }    
};
