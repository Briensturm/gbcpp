#pragma once

#include "instruction.hpp"

class SWAPR8 : public Instruction
{
    public:
        int GetInstructionLength() { return 1; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            auto registerIndex = _opcode & 0x07;

            cpuState->Registers->HalfCarryFlag = false;
            cpuState->Registers->SubtractionFlag = false;
            cpuState->Registers->CarryFlag = false;

            byte lowNibble = (byte)(cpuState->Registers->ReadRegister(registerIndex) & 0x0F);
            byte highNibble = (byte)(cpuState->Registers->ReadRegister(registerIndex) & 0xF0);

            cpuState->Registers->WriteRegister(registerIndex, (ushort)((lowNibble << 4) | (highNibble >> 4)));            

            cpuState->Registers->ZeroFlag = cpuState->Registers->ReadRegister(registerIndex) == 0;

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }
};
