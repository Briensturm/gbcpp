#pragma once

#include "instruction.hpp"

class ADDAR8 : public Instruction
{
    public:
        int GetInstructionLength() { return 1; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            auto registerIndex = _opcode & 0x07;
            auto oldValue = cpuState->Registers->A;
            auto addData = (byte)cpuState->Registers->ReadRegister(registerIndex);

            cpuState->Registers->A += addData;

            cpuState->Registers->SubtractionFlag = false;
            cpuState->Registers->ZeroFlag = cpuState->Registers->A == 0;
            cpuState->Registers->HalfCarryFlag = (((oldValue & 0xF) + (addData & 0xF)) & 0x10) == 0x10;
            cpuState->Registers->CarryFlag = cpuState->Registers->A < oldValue;

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }
};
