#pragma once

#include <memory>
#include <array>

#include "gbcpp.hpp"
#include "cpu/instructions/instruction.hpp"

class InstructionDecoder
{
    public:
        mockable InstrPtr DecodeInstruction(byte opcode);
        InstrPtr DecodePrefixedInstruction(byte opcode);
        InstrPtr GetInterruptServiceRoutineInstruction(byte readyInterrupts);
        
    private:
        void InstantiateInstructions();

        std::array<InstrPtr, 0xFF> _Instructions;
        std::array<InstrPtr, 0xFF> _prefixedInstructions;
};

using InstrDecPtr = std::shared_ptr<InstructionDecoder>;