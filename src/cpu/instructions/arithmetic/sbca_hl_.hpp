#pragma once

#include "instruction.hpp"

class SBCA_HL_ : public Instruction
{
    public:
        int GetInstructionLength() { return 2; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            switch(_remainingCycles)
            {
                case 2:
                    _subData = mainMemory->ReadByte(cpuState->Registers->HL);
                    break;
                case 1:
                {
                    auto oldValue = cpuState->Registers->A;

                    cpuState->Registers->A -= _subData;

                    if (cpuState->Registers->CarryFlag)
                        cpuState->Registers->A = cpuState->Registers->A-1;

                    cpuState->Registers->SubtractionFlag = true;
                    cpuState->Registers->ZeroFlag = cpuState->Registers->A == 0;
                    cpuState->Registers->HalfCarryFlag = ((_subData & 0x0F)
                                            + (cpuState->Registers->CarryFlag ? 1 : 0)) > (oldValue & 0xF);
                    cpuState->Registers->CarryFlag = (_subData + (cpuState->Registers->CarryFlag ? 1 : 0)) > oldValue;

                    break;
                }
            }           

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }

    private:
        byte _subData;
};
