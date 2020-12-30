#pragma once

#include "instruction.hpp"

class ADCAR8 : public Instruction
{
    public:
        int GetInstructionLength() { return 1; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            auto registerIndex = _opcode & 0x07;
            auto oldValue = cpuState->Registers->A;
            auto addData = (byte)cpuState->Registers->ReadRegister(registerIndex);

            int result = cpuState->Registers->A + addData;
            if (cpuState->Registers->CarryFlag)
                result++;

            cpuState->Registers->A = (byte)result;

            cpuState->Registers->SubtractionFlag = false;
            cpuState->Registers->ZeroFlag = cpuState->Registers->A == 0;
            cpuState->Registers->HalfCarryFlag = (((oldValue & 0xF) + (addData & 0xF)
                                                + (cpuState->Registers->CarryFlag ? 1 : 0)) & 0x10) == 0x10;
            cpuState->Registers->CarryFlag = result > 0xFF;

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }
};
