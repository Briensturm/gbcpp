#pragma once

#include "instruction.hpp"

class BITN_HL_ : public Instruction
{
    public:
        int GetInstructionLength() { return 2; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {          
            switch (_remainingCycles)
            {
                case 2:
                    _currentData = mainMemory->ReadByte(cpuState->Registers->HL);
                    break;
                case 1:
                    auto bitIndex = (_opcode & 0x38) >> 3;
                    cpuState->Registers->ZeroFlag = ((byte)(_currentData >> bitIndex) & 0x01) == 0;

                    cpuState->Registers->HalfCarryFlag = true;
                    cpuState->Registers->SubtractionFlag = false;
                    break;
            }

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }

    private:
        byte _currentData;
};
