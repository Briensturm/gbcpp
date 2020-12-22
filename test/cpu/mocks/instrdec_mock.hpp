#pragma once

#include "mock.hpp"
#include "cpu/instructions/instruction_decoder.hpp"

class InstrDecMock : public InstructionDecoder
{
    MOCK_METHOD_RET_P(InstrPtr, DecodeInstruction, byte);
};