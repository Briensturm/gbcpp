#pragma once

#include "instruction.hpp"

class SLAR8 : public Instruction
{
    public:
        int GetInstructionLength() { return 1; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            auto registerIndex = _opcode & 0x07;

            cpuState->Registers->HalfCarryFlag = false;
            cpuState->Registers->SubtractionFlag = false;

            auto hiBit = cpuState->Registers->ReadRegister(registerIndex) & 0x80;
            cpuState->Registers->CarryFlag = hiBit == 0x80;
            
            cpuState->Registers->WriteRegister(registerIndex, (ushort)(cpuState->Registers->ReadRegister(registerIndex) << 1));

            cpuState->Registers->ZeroFlag = cpuState->Registers->ReadRegister(registerIndex) == 0;

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }
};
