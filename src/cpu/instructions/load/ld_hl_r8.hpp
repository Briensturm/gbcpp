#pragma once

#include "instruction.hpp"

class LD_HL_R8 : public Instruction
{
    public:
        int GetInstructionLength() { return 2; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            switch (_remainingCycles)
            {
                case 2:
                {
                    auto registerIndex = _opcode & 0x07;
                    mainMemory->WriteByte(cpuState->Registers->HL, (byte)cpuState->Registers->ReadRegister(registerIndex));
                    break;
                }
            }                    

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }
};
