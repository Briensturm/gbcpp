#pragma once

#include "instruction.hpp"

class LDR8D8 : public Instruction
{        
    public:
        int GetInstructionLength() { return 2; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            switch (_remainingCycles)
            {
                case 2:
                    _registerIndex = _opcode >> 3;

                    _loadData = mainMemory->ReadByte(cpuState->ProgramCounter++);
                    break;
                case 1:
                    cpuState->Registers->WriteRegister(_registerIndex, _loadData);
                    break;
            }                    

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }

    private:
        byte _loadData;
        int _registerIndex;
};
