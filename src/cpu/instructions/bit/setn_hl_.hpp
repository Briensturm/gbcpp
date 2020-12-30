#pragma once

#include "instruction.hpp"

class SETN_HL_ : public Instruction
{
    public:
        int GetInstructionLength() { return 3; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {          
            switch (_remainingCycles)
            {
                case 3:
                {
                    _currentData = mainMemory->ReadByte(cpuState->Registers->HL);

                    auto bitIndex = (_opcode & 0x38) >> 3;
                    _writeData = (byte)(_currentData | (0x01 << bitIndex));
                    break;
                }
                case 2:
                    mainMemory->WriteByte(cpuState->Registers->HL, _writeData);
                    break;
            }

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }

    private:
        byte _currentData;
        byte _writeData;
};
