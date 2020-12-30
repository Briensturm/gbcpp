#pragma once

#include<stdexcept>

#include "instruction.hpp"

class ADDHLR16 : public Instruction
{
    public:
        int GetInstructionLength() { return 2; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            switch (_remainingCycles)
            {
                case 2:
                    switch(_opcode)
                    {
                        case 0x09:
                            _addData = cpuState->Registers->BC;
                            break;
                        case 0x19:
                            _addData = cpuState->Registers->DE;
                            break;
                        case 0x29:
                            _addData = cpuState->Registers->HL;
                            break;
                        case 0x39:
                            _addData = cpuState->StackPointer;
                            break;
                        default:
                            throw std::logic_error("Invalid opcode for instruction addhlr16");
                            
                    }

                    _oldValue = cpuState->Registers->HL;
                    break;
                case 1:
                    cpuState->Registers->HL += _addData;

                    cpuState->Registers->SubtractionFlag = false;                    
                    cpuState->Registers->CarryFlag = _addData > (0xFFFF - _oldValue);
                    cpuState->Registers->HalfCarryFlag = (((_addData & 0xFFF) + (_oldValue & 0xFFF)) & 0x1000) == 0x1000;
                    break;
            }

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }

    private:
        ushort _oldValue;
        ushort _addData;
};
