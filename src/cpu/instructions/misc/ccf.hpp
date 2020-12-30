#pragma once

#include "instruction.hpp"

class CCF : public Instruction
{
    public:
        int GetInstructionLength() { return 1; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)        
        {
            cpuState->Registers->SubtractionFlag = false;
            cpuState->Registers->HalfCarryFlag = false;

            cpuState->Registers->CarryFlag = !cpuState->Registers->CarryFlag;

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }
};
