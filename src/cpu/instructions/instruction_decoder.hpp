#pragma once

#include <memory>
#include <array>

#include "gbcpp.hpp"
#include "instruction.hpp"
#include "internal/ldisr.hpp"

class InstructionDecoder
{
    public:
        InstructionDecoder();
        mockable InstrPtr DecodeInstruction(byte opcode);
        InstrPtr DecodePrefixedInstruction(byte opcode);
        InstrPtr GetInterruptServiceRoutineInstruction(byte readyInterrupts);
        
    private:
        void InstantiateInstructions();

        std::array<InstrPtr, 0xFF+1> _instructions;
        std::array<InstrPtr, 0xFF+1> _prefixedInstructions; 

        std::shared_ptr<LDISR> _ldisr;
};

using InstrDecPtr = std::shared_ptr<InstructionDecoder>;