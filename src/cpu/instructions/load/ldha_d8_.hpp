#pragma once

#include "instruction.hpp"

class LDHA_D8_ : public Instruction
{
    public:
        int GetInstructionLength() { return 3; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            switch (_remainingCycles)
            {
                case 3:
                    _addressLsb = mainMemory->ReadByte(cpuState->ProgramCounter++);
                    break;
                case 2:
                    cpuState->Registers->A = mainMemory->ReadByte((ushort)((0xFF << 8) | _addressLsb));
                    break;
            }                    

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }

    private:
        byte _addressLsb;
};
