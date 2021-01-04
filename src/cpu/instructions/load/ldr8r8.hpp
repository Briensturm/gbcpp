#pragma once

#include "instruction.hpp"

class LDR8R8 : public Instruction
{
    public:
        int GetInstructionLength() { return 1; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            //register decoding
            auto sourceIndex = _opcode & 0x07;
            auto targetIndex = (_opcode >> 3) & 0x07;

            //load
            cpuState->Registers->WriteRegister(targetIndex, cpuState->Registers->ReadRegister(sourceIndex));

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }
};
