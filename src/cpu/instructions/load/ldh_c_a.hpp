#pragma once

#include "instruction.hpp"

class LDH_C_A : public Instruction
{
    public:
        int GetInstructionLength() { return 2; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            switch (_remainingCycles)
            {
                case 2:
                    mainMemory->WriteByte((ushort)((0xFF << 8) | cpuState->Registers->C), (byte)cpuState->Registers->A);
                    break;
            }                    

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }
};
