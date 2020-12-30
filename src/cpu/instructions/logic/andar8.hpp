#pragma once

#include "instruction.hpp"

class ANDAR8 : public Instruction
{
    public:
        int GetInstructionLength() { return 1; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            auto registerIndex = _opcode & 0x07;

            cpuState->Registers->A = cpuState->Registers->A & (byte)cpuState->Registers->ReadRegister(registerIndex);

            cpuState->Registers->SubtractionFlag = false;
            cpuState->Registers->ZeroFlag = cpuState->Registers->A == 0;
            cpuState->Registers->HalfCarryFlag = true;
            cpuState->Registers->CarryFlag = false;

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }
};
