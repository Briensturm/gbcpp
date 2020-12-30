#pragma once

#include "instruction.hpp"

class ADDSPS8 : public Instruction
{    
    public:
        int GetInstructionLength() { return 4; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            switch (_remainingCycles)
            {
                case 4:
                    _signedValue = (sbyte)mainMemory->ReadByte(cpuState->ProgramCounter++);
                    _oldValue = cpuState->StackPointer;
                    break;
                case 3:
                    cpuState->StackPointer = (ushort)(cpuState->StackPointer + _signedValue);
                    break;
                case 1:
                    if (_signedValue >= 0)
                    {
                        cpuState->Registers->CarryFlag = ((_oldValue & 0xFF) + (_signedValue)) > 0xFF;
                        cpuState->Registers->HalfCarryFlag = ((_oldValue & 0xF) + (_signedValue & 0xF)) > 0xF;
                    }
                    else
                    {
                        cpuState->Registers->CarryFlag = (cpuState->StackPointer & 0xFF) <= (_oldValue & 0xFF);
                        cpuState->Registers->HalfCarryFlag = (cpuState->StackPointer & 0xF) <= (_oldValue & 0xF);
                    }

                    cpuState->Registers->ZeroFlag = false;
                    cpuState->Registers->SubtractionFlag = false;                    
                    break;
            }

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }

    private:
        ushort _oldValue;
        sbyte _signedValue;
};
