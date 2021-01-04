#pragma once

#include "instruction.hpp"

class LDSPHL : public Instruction
{
    public:
        int GetInstructionLength() { return 2; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            switch (_remainingCycles)
            {
                case 1:
                    cpuState->StackPointer = cpuState->Registers->HL;
                    break;
            }                    

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }
};
