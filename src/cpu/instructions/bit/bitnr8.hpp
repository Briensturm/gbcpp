#pragma once

#include "instruction.hpp"

class BITNR8 : public Instruction
{
    public:
        int GetInstructionLength() { return 1; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            cpuState->Registers->HalfCarryFlag = true;
            cpuState->Registers->SubtractionFlag = false;

            //decode register and bit
            auto bitIndex = (_opcode & 0x38) >> 3;
            auto registerIndex = _opcode & 0x07;

            cpuState->Registers->ZeroFlag = 
                ((byte)(cpuState->Registers->ReadRegister(registerIndex) >> bitIndex) & 0x01) == 0;

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }
};
