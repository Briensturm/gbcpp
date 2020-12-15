#pragma once

#include <memory>

#include "IInstruction.hpp"
#include "InstructionDecoder.hpp"
#include "CpuState.hpp"
#include "RandomAccessMemory.hpp"

class CpuCore
{
    public:
        CpuCore(RamPtr mainMemory, CpuStatePtr cpuState);
        void AdvanceMachineCycle();
        void Reset();

    private:
        std::shared_ptr<IInstruction> GetNextInstruction();
        uint8_t GetRequestedAndEnabledInterrupts();

        bool IsCpuRunning();

        CpuStatePtr _cpuState;

        RandomAccessMemory _mainMemory;
        std::shared_ptr<IInstruction> _currentInstruction;

        InstructionDecoder _instructionDecoder;
};