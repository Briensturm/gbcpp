#pragma once

#include "instruction.hpp"

class SBCAR8 : public Instruction
{
    public:
        int GetInstructionLength() { return 1; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            auto registerIndex = _opcode & 0x07;
            auto oldValue = cpuState->Registers->A;
            auto subData = (byte)cpuState->Registers->ReadRegister(registerIndex);

            cpuState->Registers->A -= subData;

            if (cpuState->Registers->CarryFlag)
                cpuState->Registers->A = cpuState->Registers->A-1;

            cpuState->Registers->SubtractionFlag = true;
            cpuState->Registers->ZeroFlag = cpuState->Registers->A == 0;
            cpuState->Registers->HalfCarryFlag = ((subData & 0x0F)
                                            + (cpuState->Registers->CarryFlag ? 1 : 0)) > (oldValue & 0xF);
            cpuState->Registers->CarryFlag = (subData + (cpuState->Registers->CarryFlag ? 1 : 0)) > oldValue;

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }
};
