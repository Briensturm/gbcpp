#pragma once

#include "mock.hpp"
#include "registers_mock.hpp"
#include "cpu/cpu_state.hpp"

class CpuStateMock : public CpuState
{
    public:
        CpuStateMock() : CpuState(MOCK_OF<CpuRegistersMock, CpuRegisters>()) {};

    MOCK_METHOD(Reset);
};