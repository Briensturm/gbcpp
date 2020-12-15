#pragma once

#include <memory>

#include "CpuState.hpp"
#include "RandomAccessMemory.hpp"

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