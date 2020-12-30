#pragma once

#include "instruction.hpp"

class ADCA_HL_ : public Instruction
{
    public:
        int GetInstructionLength() { return 2; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            switch (_remainingCycles)
            {
                case 2:
                    _addData = mainMemory->ReadByte(cpuState->Registers->HL);
                    break;
                case 1:
                {
                    auto oldValue = cpuState->Registers->A;

                    int result = cpuState->Registers->A + _addData;
                    if (cpuState->Registers->CarryFlag)
                        result++;

                    cpuState->Registers->A = (byte)result;

                    cpuState->Registers->SubtractionFlag = false;
                    cpuState->Registers->ZeroFlag = cpuState->Registers->A == 0;
                    cpuState->Registers->HalfCarryFlag = (((oldValue & 0xF) + (_addData & 0xF)
                                                + (cpuState->Registers->CarryFlag ? 1 : 0)) & 0x10) == 0x10;
                    cpuState->Registers->CarryFlag = result > 0xFF;

                    break;
                }
            }

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }

    private:
        byte _addData;
};
