#pragma once

#include "instruction.hpp"

class CPAR8 : public Instruction
{
    public:
        int GetInstructionLength() { return 1; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            auto registerIndex = _opcode & 0x07;

            cpuState->Registers->SubtractionFlag = true;
            cpuState->Registers->ZeroFlag = cpuState->Registers->A - (byte)cpuState->Registers->ReadRegister(registerIndex) == 0;
            cpuState->Registers->HalfCarryFlag = ((cpuState->Registers->A & 0xF) - (cpuState->Registers->ReadRegister(registerIndex) & 0xF)) < 0;
            cpuState->Registers->CarryFlag = (byte)cpuState->Registers->ReadRegister(registerIndex) > cpuState->Registers->A;

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }
};
