#pragma once

#include <memory>
#include <stdexcept>

#include "gbcpp.hpp"
#include "cpu_registers.hpp"

class CpuState
{
    public:
        CpuState(RegistersPtr cpuRegisters) : Registers(cpuRegisters) 
        {
            if(cpuRegisters == nullptr)
                throw std::invalid_argument("CpuRegisters must not be null.");
        }

        mockable void Reset();

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