#pragma once

#include "instruction.hpp"

class INCR16 : public Instruction
{
    public:
        int GetInstructionLength() { return 2; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            switch(_remainingCycles)
            {
                case 2:
                    _registerBits = (byte)((_opcode >> 4) & 0x03);
                    break;
                case 1:
                    switch(_registerBits)
                    {
                        case 0b00:
                            cpuState->Registers->BC = cpuState->Registers->BC+1;
                            break;
                        case 0b01:
                            cpuState->Registers->DE = cpuState->Registers->DE+1;
                            break;
                        case 0b10:
                            cpuState->Registers->HL = cpuState->Registers->HL+1;
                            break;
                        case 0b11:
                            cpuState->StackPointer++;
                            break;
                    }
                    break;
            }
            Instruction::ExecuteCycle(cpuState, mainMemory);
        }

    private:
        byte _registerBits;
};
