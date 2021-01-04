#pragma once

#include "instruction.hpp"

class LD_BC_A : public Instruction
{
    public:
        int GetInstructionLength() { return 2; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            switch (_remainingCycles)
            {
                case 2:
                    mainMemory->WriteByte(cpuState->Registers->BC, (byte)cpuState->Registers->A);
                    break;
            }                    

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }
};
