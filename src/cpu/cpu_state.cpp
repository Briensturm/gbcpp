#include "cpu_state.hpp"

void CpuState::Reset()
{
    ProgramCounter = 0x0100;
    StackPointer = 0xFFFE;
    
    InterruptMasterEnable = false;
    InstructionPrefix = false;
    HaltMode = false;
    HaltBug = false;
    StopMode = false;

    ImeScheduled = false;            

    Registers->Reset();
}