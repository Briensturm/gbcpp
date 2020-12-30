#pragma once

#include "instruction.hpp"

class RST : public Instruction
{
    public:
        int GetInstructionLength() { return 4; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            switch(_remainingCycles)
            {
                case 4:
                    //calculate jump address
                    _jumpAddress = (ushort)(_opcode & 0x38);
                    break;
                case 3:
                    //write msb of program counter to stack
                    mainMemory->WriteByte(--cpuState->StackPointer, (byte)(cpuState->ProgramCounter >> 8));                    
                    break;
                case 2:
                    //write lsb of program counter to stack
                    mainMemory->WriteByte(--cpuState->StackPointer, (byte)(cpuState->ProgramCounter & 0x00FF));
                    break;
                case 1:
                    //do the jump
                    cpuState->ProgramCounter = _jumpAddress;
                    break;
            }

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }

    private:
        ushort _jumpAddress;
};
