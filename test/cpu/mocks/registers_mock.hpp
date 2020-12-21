#pragma once

#include <memory>

#include "mock.hpp"
#include "cpu/cpu_registers.hpp"

class CpuRegistersMock : public CpuRegisters
{
    MOCK_METHOD(Reset);
};