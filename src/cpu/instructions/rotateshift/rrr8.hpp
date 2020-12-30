#pragma once

#include "instruction.hpp"

class RRR8 : public Instruction
{
    public:
        int GetInstructionLength() { return 1; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            auto registerIndex = _opcode & 0x07;

            cpuState->Registers->HalfCarryFlag = false;
            cpuState->Registers->SubtractionFlag = false;

            auto bit = cpuState->Registers->ReadRegister(registerIndex) & 0x01;            
            auto newVal = (ushort)(cpuState->Registers->ReadRegister(registerIndex) >> 1);            
                
            if (cpuState->Registers->CarryFlag)
                cpuState->Registers->WriteRegister(registerIndex, newVal |= 0x80);
            else
                cpuState->Registers->WriteRegister(registerIndex, newVal);            

            cpuState->Registers->CarryFlag = bit == 1;
            cpuState->Registers->ZeroFlag = cpuState->Registers->ReadRegister(registerIndex) == 0;

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }
};
