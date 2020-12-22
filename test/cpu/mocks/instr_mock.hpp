#pragma once

#include "mock.hpp"
#include "cpu/instructions/instruction.hpp"

class InstrMock : public Instruction
{
    MOCK_METHOD_RET(int, GetInstructionLength);
};