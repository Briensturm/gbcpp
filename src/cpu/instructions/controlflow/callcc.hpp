#pragma once

#include "instruction.hpp"

class CALLCC : public Instruction
{
    public:
        int GetInstructionLength() { return 6; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            switch(_remainingCycles)
            {
                case 6:
                    //read jump address lsb
                    _jumpAddress = mainMemory->ReadByte(cpuState->ProgramCounter++);
                    break;
                case 5:
                    //read jump address msb
                    _jumpAddress |= (ushort)(mainMemory->ReadByte(cpuState->ProgramCounter++) << 8);
                    break;
                case 4:
                    //set last cycle if condition is not met
                    if (!IsConditionMet(cpuState))
                        _remainingCycles = 1;
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
