#pragma once

#include "instruction.hpp"

class JR : public Instruction
{
    public:
        int GetInstructionLength() { return 3; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            switch(_remainingCycles)
            {
                case 3:
                    //read jump address lsb
                    _relativeAddress = (sbyte)mainMemory->ReadByte(cpuState->ProgramCounter++);
                    break;
                case 1:
                    //do the jump
                    cpuState->ProgramCounter = (ushort)(cpuState->ProgramCounter + _relativeAddress);
                    break;
            }

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }

    private:
        sbyte _relativeAddress;
};
