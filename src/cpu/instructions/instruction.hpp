#pragma once

#include <memory>

#include "cpu_state.hpp"
#include "ram.hpp"

class IInstruction
{
    public:
        virtual void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory);
        bool IsFetchNecessary();
        void Initialize(uint8_t opcode);

    protected:
        int _remainingCycles;
        uint8_t _opcode;

        virtual int GetInstructionLength() = 0;
        bool IsConditionMet(const CpuStatePtr& cpuState);     
};