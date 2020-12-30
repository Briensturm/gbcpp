#pragma once

#include "instruction.hpp"

class SUBAD8 : public Instruction
{
    public:
        int GetInstructionLength() { return 2; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            switch (_remainingCycles)
            {
                case 2:
                    _subData = mainMemory->ReadByte(cpuState->ProgramCounter++);
                    break;
                case 1:
                {
                    auto oldValue = cpuState->Registers->A;

                    cpuState->Registers->A -= _subData;

                    cpuState->Registers->SubtractionFlag = true;
                    cpuState->Registers->ZeroFlag = cpuState->Registers->A == 0;
                    cpuState->Registers->HalfCarryFlag = ((oldValue & 0xF) - (_subData & 0xF)) < 0;
                    cpuState->Registers->CarryFlag = _subData > oldValue;

                    break;
                }
            }

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }

    private:
        byte _subData;
};
