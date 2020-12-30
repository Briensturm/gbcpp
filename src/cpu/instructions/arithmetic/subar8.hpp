#pragma once

#include "instruction.hpp"

class SUBAR8 : public Instruction
{
    public:
        int GetInstructionLength() { return 1; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            auto registerIndex = _opcode & 0x07;
            auto oldValue = cpuState->Registers->A;
            auto subData = (byte)cpuState->Registers->ReadRegister(registerIndex);

            cpuState->Registers->A -= subData;

            cpuState->Registers->SubtractionFlag = true;
            cpuState->Registers->ZeroFlag = cpuState->Registers->A == 0;
            cpuState->Registers->HalfCarryFlag = ((oldValue & 0xF) - (subData & 0xF)) < 0;
            cpuState->Registers->CarryFlag = subData > oldValue;

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }
};
