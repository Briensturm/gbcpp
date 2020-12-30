#pragma once

#include "instruction.hpp"

class DI : public Instruction
{
    public:
        int GetInstructionLength() { return 1; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            cpuState->InterruptMasterEnable = false;
            cpuState->ImeScheduled = false;

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }
};
