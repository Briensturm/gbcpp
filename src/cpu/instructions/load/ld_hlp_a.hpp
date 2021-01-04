#pragma once

#include "instruction.hpp"

class LD_HLP_A : public Instruction
{
    public:
        int GetInstructionLength() { return 2; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            switch (_remainingCycles)
            {
                case 2:
                    mainMemory->WriteByte(cpuState->Registers->HL, (byte)cpuState->Registers->A);
                    break;
                case 1:
                    cpuState->Registers->HL = cpuState->Registers->HL+1;
                    break;
            }                    

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }
};
