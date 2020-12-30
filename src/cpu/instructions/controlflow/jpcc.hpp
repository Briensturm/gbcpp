#pragma once

#include "instruction.hpp"

class JPCC : public Instruction
{
    public:
        int GetInstructionLength() { return 4; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            switch(_remainingCycles)
            {
                case 4:
                    //read jump address lsb
                    _jumpAddress = mainMemory->ReadByte(cpuState->ProgramCounter++);
                    break;
                case 3:
                    //read jump address msb
                    _jumpAddress |= (ushort)(mainMemory->ReadByte(cpuState->ProgramCounter++) << 8);
                    break;
                case 2:
                    //set last cycle if condition is not met
                    if (!IsConditionMet(cpuState))
                        _remainingCycles = 1;
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
