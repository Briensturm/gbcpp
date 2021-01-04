#pragma once

#include "instruction.hpp"

class LDA_HLM_ : public Instruction
{
    public:
        int GetInstructionLength() { return 2; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            switch (_remainingCycles)
            {
                case 2:
                    cpuState->Registers->A = mainMemory->ReadByte(cpuState->Registers->HL);
                    break;
                case 1:
                    cpuState->Registers->HL = cpuState->Registers->HL-1;
                    break;
            }                    

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }
};
