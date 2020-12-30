#pragma once

#include "instruction.hpp"

class PUSH : public Instruction
{
    public:
        int GetInstructionLength() { return 4; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            switch(_remainingCycles)
            {
                case 4:                        
                    _registerBits = (byte)((_opcode >> 4) & 0x03);                        
                    LoadWriteData(cpuState);                    
                    break;
                case 3:
                    mainMemory->WriteByte(--cpuState->StackPointer, _msbData);
                    break;
                case 2:
                    mainMemory->WriteByte(--cpuState->StackPointer, _lsbData);
                    break;
            }

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }

    private:
        byte _registerBits;
        byte _msbData;
        byte _lsbData;

        void LoadWriteData(CpuStatePtr& cpuState)
        {
            switch(_registerBits)
            {
                case 0b00:
                    _msbData = (byte)cpuState->Registers->B;
                    _lsbData = (byte)cpuState->Registers->C;
                    break;
                case 0b01:
                    _msbData = (byte)cpuState->Registers->D;
                    _lsbData = (byte)cpuState->Registers->E;
                    break;
                case 0b10:
                    _msbData = (byte)cpuState->Registers->H;
                    _lsbData = (byte)cpuState->Registers->L;
                    break;
                case 0b11:
                    _msbData = (byte)cpuState->Registers->A;
                    _lsbData = (byte)cpuState->Registers->F;
                    break;
            }
        }    
};
