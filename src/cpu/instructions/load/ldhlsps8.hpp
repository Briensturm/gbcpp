#pragma once

#include "instruction.hpp"

class LDHLSPS8 : public Instruction
{
    public:
        int GetInstructionLength() { return 3; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            switch (_remainingCycles)
            {
                case 3:
                    _signedValue = (sbyte)mainMemory->ReadByte(cpuState->ProgramCounter++);
                    break;
                case 2:
                    cpuState->Registers->HL = (ushort)(cpuState->StackPointer + _signedValue);
                    break;
                case 1:
                    if (_signedValue >= 0)
                    {
                        cpuState->Registers->CarryFlag = ((cpuState->StackPointer & 0xFF) + (_signedValue)) > 0xFF;
                        cpuState->Registers->HalfCarryFlag = ((cpuState->StackPointer & 0xF) + (_signedValue & 0xF)) > 0xF;
                    }
                    else
                    {
                        cpuState->Registers->CarryFlag = ((cpuState->StackPointer + _signedValue) & 0xFF) <= (cpuState->StackPointer & 0xFF);
                        cpuState->Registers->HalfCarryFlag = ((cpuState->StackPointer + _signedValue) & 0xF) <= (cpuState->StackPointer & 0xF);
                    }

                    cpuState->Registers->ZeroFlag = false;
                    cpuState->Registers->SubtractionFlag = false;                    
                    break;                
            }            

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }

    private:
        sbyte _signedValue;
};
