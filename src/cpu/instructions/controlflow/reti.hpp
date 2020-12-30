﻿#pragma once

#include "instruction.hpp"

class RETI : public Instruction
{
    public:
        int GetInstructionLength() { return 4; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            switch(_remainingCycles)
            {
                case 4:
                    //read jump address lsb
                    _jumpAddress = mainMemory->ReadByte(cpuState->StackPointer++);
                    break;
                case 3:
                    //read jump address msb
                    _jumpAddress |= (ushort)(mainMemory->ReadByte(cpuState->StackPointer++) << 8);
                    break;
                case 2:
                    cpuState->ImeScheduled = true;
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
