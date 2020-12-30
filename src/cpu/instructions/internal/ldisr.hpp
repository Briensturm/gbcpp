#pragma once

#include "cpu/instructions/instruction.hpp"

using namespace constants;

class LDISR : public Instruction
{        
    public:
        int GetInstructionLength() { return 5; }

        void Prepare(byte readyInterrupts)
        {
            _readyInterrupts = readyInterrupts;
            _remainingCycles = GetInstructionLength();
        }

        void ExecuteCycle(CpuStatePtr& cpuState, RamPtr& mainMemory)
        {
            switch(_remainingCycles)
            {
                case 3:
                    mainMemory->WriteByte(--cpuState->StackPointer, (byte)(cpuState->ProgramCounter >> 8));
                    break;
                case 2:
                    mainMemory->WriteByte(--cpuState->StackPointer, (byte)(cpuState->ProgramCounter & 0x00FF));
                    break;
                case 1:
                {
                    auto interruptFlags = mainMemory->ReadByte(reg::int_flags);

                    //vblank interrupt
                    if ((_readyInterrupts & 0x01) == 0x01)
                    {
                        //Console.WriteLine("Loading vblank isr...");

                        cpuState->ProgramCounter = int_addr::vblank;

                        mainMemory->WriteByte(reg::int_flags, (byte)(interruptFlags & 0xFE));
                    }

                    //lcd stat interrupt
                    else if ((_readyInterrupts & 0x02) == 0x02)
                    {
                        //Console.WriteLine("Loading lcd stat isr...");

                        cpuState->ProgramCounter = int_addr::lcd;

                        //clear interrupt flag
                        mainMemory->WriteByte(reg::int_flags, (byte)(interruptFlags & 0xFD));
                    }
                    
                    //timer interrupt
                    else if ((_readyInterrupts & 0x04) == 0x04)
                    {
                        //Console.WriteLine("Loading timer isr...");

                        cpuState->ProgramCounter = int_addr::timer;

                        //clear interrupt flag
                        mainMemory->WriteByte(reg::int_flags, (byte)(interruptFlags & 0xFB));
                    }

                    //serial interrupt
                    else if ((_readyInterrupts & 0x08) == 0x08)
                    {
                        cpuState->ProgramCounter = int_addr::serial;

                        //clear interrupt flag
                        mainMemory->WriteByte(reg::int_flags, (byte)(interruptFlags & 0xF7));
                    }

                    //joypad interrupt
                    else if ((_readyInterrupts & 0x10) == 0x10)
                    {
                        cpuState->ProgramCounter = int_addr::joypad;

                        //clear interrupt flag
                        mainMemory->WriteByte(reg::int_flags, (byte)(interruptFlags & 0x0F));
                    }

                    cpuState->InterruptMasterEnable = false;
                    break;
                }
            }            

            Instruction::ExecuteCycle(cpuState, mainMemory);
        }

    private:
        byte _readyInterrupts;
};
