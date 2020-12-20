#pragma once

#include <memory>

#include "cpu_registers.hpp"
#include "types.hpp"

class CpuState
{
    public:
        CpuState(RegistersPtr cpuRegisters)
                    : Registers(cpuRegisters) {}

        void Reset();

        ushort ProgramCounter;
        ushort StackPointer;

        bool InterruptMasterEnable;
        bool ImeScheduled;
        bool HaltMode;
        bool HaltBug;
        bool StopMode;
        bool InstructionPrefix;

        RegistersPtr Registers;
};

using CpuStatePtr = std::shared_ptr<CpuState>;