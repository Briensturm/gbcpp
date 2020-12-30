#pragma once

#include "instruction.hpp"

class INC_HL_ : public Instruction
{
    public:
        int GetInstructionLength() { return 3; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            switch(_remainingCycles)
            {
                case 3:
                    _currentData = mainMemory->ReadByte(cpuState->Registers->HL);
                    break;
                case 2:
                    _incrementedData = (byte)(_currentData + 1);
                    mainMemory->WriteByte(cpuState->Registers->HL, _incrementedData);
                    break;
                case 1:
                    cpuState->Registers->ZeroFlag = _incrementedData == 0;
                    cpuState->Registers->SubtractionFlag = false;
                    cpuState->Registers->HalfCarryFlag = (_incrementedData & 0x0F) == 0;
                    break;
            }
            Instruction::ExecuteCycle(cpuState, mainMemory);
        }

    private:
        byte _currentData;
        byte _incrementedData;
};
