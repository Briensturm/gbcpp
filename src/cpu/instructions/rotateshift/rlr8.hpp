#pragma once

#include "instruction.hpp"

class RLR8 : public Instruction
{
    public:
        int GetInstructionLength() { return 1; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            auto registerIndex = _opcode & 0x07;

            cpuState->Registers->HalfCarryFlag = false;
            cpuState->Registers->SubtractionFlag = false;

            auto bit = cpuState->Registers->ReadRegister(registerIndex) >> 7;            
            
            auto writeVal = (ushort)(cpuState->Registers->ReadRegister(registerIndex) << 1);
            
            if (cpuState->Registers->CarryFlag)
                cpuState->Registers->WriteRegister(registerIndex, writeVal | 0x01);
            else
                cpuState->Registers->WriteRegister(registerIndex, writeVal);

            cpuState->Registers->ZeroFlag = cpuState->Registers->ReadRegister(registerIndex) == 0;
            cpuState->Registers->CarryFlag = bit == 1;

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }
};
