#pragma once

#include "instruction.hpp"

class RRCA : public Instruction
{
    public:
        int GetInstructionLength() { return 1; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            cpuState->Registers->HalfCarryFlag = false;
            cpuState->Registers->SubtractionFlag = false;
            cpuState->Registers->ZeroFlag = false;

            auto bit = cpuState->Registers->A & 0x01;            
            
            cpuState->Registers->A = (byte)((cpuState->Registers->A >> 1) | (byte)(bit << 7));

            cpuState->Registers->CarryFlag = bit == 1;

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }
};
