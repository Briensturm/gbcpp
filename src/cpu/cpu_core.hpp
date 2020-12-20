#pragma once

#include <memory>

#include "instructions/instruction.hpp"
#include "instructions/instruction_decoder.hpp"
#include "cpu_state.hpp"
#include "ram.hpp"

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