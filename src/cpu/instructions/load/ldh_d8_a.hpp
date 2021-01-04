#pragma once

#include "instruction.hpp"

class LDH_D8_A : public Instruction
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
                    mainMemory->WriteByte((ushort)((0xFF << 8) | _addressLsb), (byte)cpuState->Registers->A);
                    break;
            }                    

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }

    private:
        byte _addressLsb;
};
