#pragma once

#include <memory>

#include "gbcpp.hpp"
#include "cpu/cpu_state.hpp"
#include "ram/ram.hpp"

class Instruction
{
    public:
        virtual void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory);
        mockable bool IsFetchNecessary();
        mockable void Initialize(byte opcode);

    protected:
        int _remainingCycles;
        byte _opcode;

        virtual int GetInstructionLength() = 0;
        bool IsConditionMet(const CpuStatePtr& cpuState);     
};

using InstrPtr = std::shared_ptr<Instruction>;