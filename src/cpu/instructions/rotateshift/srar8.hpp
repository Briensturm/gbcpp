#pragma once

#include "instruction.hpp"

class SRAR8 : public Instruction
{
    public:
        int GetInstructionLength() { return 1; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            auto registerIndex = _opcode & 0x07;

            cpuState->Registers->HalfCarryFlag = false;
            cpuState->Registers->SubtractionFlag = false;

            auto hiBit = cpuState->Registers->ReadRegister(registerIndex) & 0x80;
            auto loBit = cpuState->Registers->ReadRegister(registerIndex) & 0x01;
            cpuState->Registers->CarryFlag = loBit == 0x01;
            
            cpuState->Registers->WriteRegister(registerIndex, (ushort)(cpuState->Registers->ReadRegister(registerIndex) >> 1));
            cpuState->Registers->WriteRegister(registerIndex, (ushort)(cpuState->Registers->ReadRegister(registerIndex) | (ushort)hiBit));

            cpuState->Registers->ZeroFlag = cpuState->Registers->ReadRegister(registerIndex) == 0;

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }
};
