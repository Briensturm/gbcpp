#pragma once

#include "instruction.hpp"

class RL_HL_ : public Instruction
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
                    _bit = _currentData >> 7;

                    _writeData = (byte)(_currentData << 1);
                    if (cpuState->Registers->CarryFlag)
                        _writeData |= 0x01;

                    mainMemory->WriteByte(cpuState->Registers->HL, _writeData);

                    cpuState->Registers->CarryFlag = _bit == 1;
                    cpuState->Registers->ZeroFlag = _writeData == 0;
                    cpuState->Registers->HalfCarryFlag = false;
                    cpuState->Registers->SubtractionFlag = false;
                    break;
            }            

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }

    private:
        byte _currentData;
        byte _writeData;
        int _bit;
};
