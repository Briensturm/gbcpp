#pragma once

#include "instruction.hpp"

class LD_DE_A : public Instruction
{
    public:
        int GetInstructionLength() { return 2; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            switch (_remainingCycles)
            {
                case 2:
                    mainMemory->WriteByte(cpuState->Registers->DE, (byte)cpuState->Registers->A);
                    break;
            }                    

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }
};
