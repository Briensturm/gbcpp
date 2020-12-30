#pragma once

#include "instruction.hpp"

class ADDA_HL_ : public Instruction
{
    public:
        int GetInstructionLength() { return 2; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            switch(_remainingCycles)
            {
                case 2:
                    _addData = mainMemory->ReadByte(cpuState->Registers->HL);
                    break;
                case 1:
                {
                    auto oldValue = cpuState->Registers->A;

                    cpuState->Registers->A += _addData;

                    cpuState->Registers->SubtractionFlag = false;
                    cpuState->Registers->ZeroFlag = cpuState->Registers->A == 0;
                    cpuState->Registers->HalfCarryFlag = (((oldValue & 0xF) + (_addData & 0xF)) & 0x10) == 0x10;
                    cpuState->Registers->CarryFlag = cpuState->Registers->A < oldValue;

                    break;
                }
            }           

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }

    private:
        byte _addData;
};
