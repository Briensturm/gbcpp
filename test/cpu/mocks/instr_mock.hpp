#pragma once

#include "mock.hpp"
#include "cpu/instructions/instruction.hpp"

class InstrMock : public Instruction
{
    MOCK_METHOD_RET(int, GetInstructionLength);

    //NOP
    public:
        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            this->_remainingCycles--;
            ExecuteCycleCalled++;
        }
        int ExecuteCycleCalled = 0;
};