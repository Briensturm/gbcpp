#pragma once

#include <memory>
#include <stdexcept>

#include "gbcpp.hpp"
#include "cpu/instructions/instruction.hpp"
#include "cpu/instructions/instruction_decoder.hpp"
#include "cpu/cpu_state.hpp"
#include "ram/ram.hpp"

class CpuCore
{
    public:
        CpuCore(RamPtr ram, CpuStatePtr cpuState, InstrDecPtr instrDec)
                    : _ram(ram), _cpuState(cpuState), _instrDecoder(instrDec) 
        {
            if(ram == nullptr)
                throw std::invalid_argument("RamPtr must not be nullptr.");
            if(cpuState == nullptr)
                throw std::invalid_argument("CpuStatePtr must not be nullptr.");
            if(instrDec == nullptr)
                throw std::invalid_argument("InstrDecPtr must not be nullptr.");

            //TODO: check if resetting at this point is necessary.
            //Reset();
        }

        void AdvanceMachineCycle();
        void Reset();

    private:
        std::shared_ptr<Instruction> GetNextInstruction();
        byte GetRequestedAndEnabledInterrupts() const;

        bool IsCpuRunning() const;

        InstrPtr GetCurrentInstruction();

        CpuStatePtr _cpuState;
        RamPtr _ram;

        InstrDecPtr _instrDecoder;
        InstrPtr _currentInstruction;
};

using CpuCorePtr = std::shared_ptr<CpuCore>;