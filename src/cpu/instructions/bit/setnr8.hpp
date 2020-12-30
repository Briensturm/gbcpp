#pragma once

#include "instruction.hpp"

class SETNR8 : public Instruction
{
    public:
        int GetInstructionLength() { return 1; }

    void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
    {
        //decode register and bit
        auto bitIndex = (_opcode & 0x38) >> 3;
        auto registerIndex = _opcode & 0x07;

        cpuState->Registers->WriteRegister(registerIndex, 
            (ushort)(cpuState->Registers->ReadRegister(registerIndex) | (0x01 << bitIndex)));

        Instruction::ExecuteCycle(cpuState, mainMemory);
    }
};