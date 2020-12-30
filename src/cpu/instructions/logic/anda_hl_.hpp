#pragma once

#include "instruction.hpp"

class ANDA_HL_ : public Instruction
{
    public:
        int GetInstructionLength() { return 2; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            switch(_remainingCycles)
            {
                case 2:
                    _data = mainMemory->ReadByte(cpuState->Registers->HL);
                    break;
                case 1:
                    cpuState->Registers->A = cpuState->Registers->A & _data;
                    break;
            }            

            cpuState->Registers->SubtractionFlag = false;
            cpuState->Registers->ZeroFlag = cpuState->Registers->A == 0;
            cpuState->Registers->HalfCarryFlag = true;
            cpuState->Registers->CarryFlag = false;

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }

    private:
        byte _data;
};
