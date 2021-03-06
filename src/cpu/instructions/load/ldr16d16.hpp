﻿#pragma once

#include "instruction.hpp"

class LDR16D16 : public Instruction
{        
    public:
        int GetInstructionLength() { return 3; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            switch (_remainingCycles)
            {
                case 3:
                    _registerBits = (byte)((_opcode >> 4) & 0x03);

                    _loadData = mainMemory->ReadByte(cpuState->ProgramCounter++);
                    break;
                case 2:
                    _loadData |= (ushort)(mainMemory->ReadByte(cpuState->ProgramCounter++) << 8);
                    break;
                case 1:
                    switch (_registerBits)
                    {
                        case 0b00:
                            cpuState->Registers->BC = _loadData;
                            break;
                        case 0b01:
                            cpuState->Registers->DE = _loadData;
                            break;
                        case 0b10:
                            cpuState->Registers->HL = _loadData;
                            break;
                        case 0b11:
                            cpuState->StackPointer = _loadData;
                            break;
                    }
                    break;
            }                    

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }

    private:
        byte _registerBits;
        ushort _loadData;
};
