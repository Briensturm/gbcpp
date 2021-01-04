#pragma once

#include "instruction.hpp"

class LD_D16_A : public Instruction
{
    public:
        int GetInstructionLength() { return 4; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            switch (_remainingCycles)
            {
                case 4:
                    _address = mainMemory->ReadByte(cpuState->ProgramCounter++);
                    break;
                case 3:
                    _address |= (ushort)(mainMemory->ReadByte(cpuState->ProgramCounter++) << 8);
                    break;
                case 2:
                    mainMemory->WriteByte(_address, (byte)cpuState->Registers->A);
                    break;
            }                    

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }

    private:
        ushort _address;
};
