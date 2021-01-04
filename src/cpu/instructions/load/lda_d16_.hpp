#pragma once

#include "instruction.hpp"

class LDA_D16_ : public Instruction
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
                    _writeData = mainMemory->ReadByte(_address);
                    break;
                case 1:
                    cpuState->Registers->A = _writeData;
                    break;
            }                    

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }

    private:
        ushort _address;
        byte _writeData;
};
