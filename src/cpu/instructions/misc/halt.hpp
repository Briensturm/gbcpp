#pragma once

#include "instruction.hpp"

using namespace constants;

class HALT : public Instruction
{
    public:
        int GetInstructionLength() { return 1; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            auto interruptEnable = mainMemory->ReadByte(reg::int_enable);
            auto interruptFlags = mainMemory->ReadByte(reg::int_flags);

            if (!cpuState->InterruptMasterEnable && (interruptEnable & interruptFlags & 0x1F) != 0)
                cpuState->HaltBug = true;    
            else
                cpuState->HaltMode = true;

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }    
};
