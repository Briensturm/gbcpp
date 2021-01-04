#pragma once

#include "instruction.hpp"

class LDA_DE_ : public Instruction
{
    public:
        int GetInstructionLength() { return 2; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            switch (_remainingCycles)
            {
                case 2:
                    _loadData = mainMemory->ReadByte(cpuState->Registers->DE);
                    break;
                case 1:
                    cpuState->Registers->A = _loadData;
                    break;
            }                    

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }

    private:
        byte _loadData;
};
