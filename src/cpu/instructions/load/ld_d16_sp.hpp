#pragma once

#include "instruction.hpp"

class LD_D16_SP : public Instruction
{
    public:
        int GetInstructionLength() { return 5; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            switch (_remainingCycles)
            {
                case 5:
                    _writeAddress = mainMemory->ReadByte(cpuState->ProgramCounter++);
                    break;
                case 4:
                    _writeAddress |= (ushort)(mainMemory->ReadByte(cpuState->ProgramCounter++) << 8);                    
                    break;
                case 3:
                    //write lsb of stack pointer
                    mainMemory->WriteByte(_writeAddress, (byte)cpuState->StackPointer);
                    break;
                case 2:
                    //write msb of stack pointer
                    mainMemory->WriteByte((ushort)(_writeAddress + 1), (byte)(cpuState->StackPointer >> 8));
                    break;
                case 1:
                    break;
            }                    

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }

    private:
        ushort _writeAddress;
};
