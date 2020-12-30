#pragma once

#include "instruction.hpp"

class DEC_HL_ : public Instruction
{    
    public:
        int GetInstructionLength() { return 3; }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            switch(_remainingCycles)
            {
                case 3:
                    _currentData = mainMemory->ReadByte(cpuState->Registers->HL);
                    break;
                case 2:
                    _decrementedData = (byte)(_currentData - 1);
                    mainMemory->WriteByte(cpuState->Registers->HL, _decrementedData);
                    break;
                case 1:
                    cpuState->Registers->ZeroFlag = _decrementedData == 0;
                    cpuState->Registers->SubtractionFlag = true;
                    cpuState->Registers->HalfCarryFlag = (_currentData & 0x0F) == 0;
                    break;
            }
            Instruction::ExecuteCycle(cpuState, mainMemory);
        }

    private:
        byte _currentData;
        byte _decrementedData;
};
