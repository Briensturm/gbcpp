#pragma once

#include "instruction.hpp"

class LDHA_C_ : public Instruction
{
    public:
        int GetInstructionLength() { return 2; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            switch (_remainingCycles)
            {
                case 2:
                    cpuState->Registers->A = mainMemory->ReadByte((ushort)((0xFF << 8) | cpuState->Registers->C));
                    break;
            }                    

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }
};
