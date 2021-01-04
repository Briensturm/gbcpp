#pragma once

#include "instruction.hpp"

class RLCR8 : public Instruction
{
    public:
        int GetInstructionLength() { return 1; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            cpuState->Registers->HalfCarryFlag = false;
            cpuState->Registers->SubtractionFlag = false;

            auto bit = cpuState->Registers->ReadRegister(_opcode) >> 7;
            cpuState->Registers->CarryFlag = bit == 1;

            cpuState->Registers->WriteRegister(_opcode, (ushort)((cpuState->Registers->ReadRegister(_opcode) << 1) | bit));
            cpuState->Registers->ZeroFlag = cpuState->Registers->ReadRegister(_opcode) == 0;

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }
};
