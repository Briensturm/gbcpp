#pragma once

#include "instruction.hpp"

class CPAD8 : public Instruction
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
                    cpuState->Registers->SubtractionFlag = true;
                    cpuState->Registers->ZeroFlag = cpuState->Registers->A - _subData == 0;
                    cpuState->Registers->HalfCarryFlag = ((cpuState->Registers->A & 0xF) - (_subData & 0xF)) < 0;
                    cpuState->Registers->CarryFlag = _subData > cpuState->Registers->A;

                    break;
            }

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }

    private:
        byte _subData;
};
