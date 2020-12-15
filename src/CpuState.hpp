#pragma once

#include <memory>

#include "CpuRegisters.hpp"

class CpuState
{
    public:
        CpuState(std::shared_ptr<CpuRegisters> cpuRegisters)
                                 : Registers(cpuRegisters) {}

        void Reset();

        unsigned short ProgramCounter;
        unsigned short StackPointer;

        bool InterruptMasterEnable;
        bool ImeScheduled;
        bool HaltMode;
        bool HaltBug;
        bool StopMode;
        bool InstructionPrefix;

        std::shared_ptr<CpuRegisters> Registers;
};

using CpuStatePtr = std::shared_ptr<CpuState>;