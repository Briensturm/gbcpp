#pragma once

#include "instruction.hpp"

class SWAP_HL_ : public Instruction
{
    public:
        int GetInstructionLength() { return 3; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            switch (_remainingCycles)
            {
                case 3:
                    _currentData = mainMemory->ReadByte(cpuState->Registers->HL);
                    break;
                case 2:
                {
                    byte lowNibble = (byte)(_currentData & 0x0F);
                    byte highNibble = (byte)(_currentData & 0xF0);

                    _writeData = (byte)((lowNibble << 4) | (highNibble >> 4));                    

                    mainMemory->WriteByte(cpuState->Registers->HL, _writeData);

                    cpuState->Registers->ZeroFlag = _writeData == 0;
                    cpuState->Registers->HalfCarryFlag = false;
                    cpuState->Registers->SubtractionFlag = false;
                    cpuState->Registers->CarryFlag = false;
                    break;
                }
            }           

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }

    private:
        byte _currentData;
        byte _writeData;
};
