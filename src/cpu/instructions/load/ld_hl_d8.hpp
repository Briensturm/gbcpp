#pragma once

#include "instruction.hpp"

class LD_HL_D8 : public Instruction
{
    public:
        int GetInstructionLength() { return 3; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            switch (_remainingCycles)
            {
                case 3:
                    _loadData = mainMemory->ReadByte(cpuState->ProgramCounter++);
                    break;
                case 2:
                    mainMemory->WriteByte(cpuState->Registers->HL, _loadData);
                    break;
            }                    

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }

    private:
        byte _loadData;
};
