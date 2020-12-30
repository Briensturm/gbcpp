#include "instruction_decoder.hpp"

#include "controlflow/call.hpp"
#include "bit/bitn_hl_.hpp"
#include "bit/bitnr8.hpp"
#include "bit/resn_hl_.hpp"
#include "bit/resnr8.hpp"
#include "bit/setn_hl_.hpp"
#include "bit/setnr8.hpp"
#include "misc/ccf.hpp"
#include "misc/cpl.hpp"
#include "misc/daa.hpp"
#include "misc/di.hpp"
#include "misc/ei.hpp"
#include "misc/halt.hpp"
#include "misc/nop.hpp"
#include "misc/pop.hpp"
#include "misc/prefix.hpp"
#include "misc/push.hpp"
#include "misc/scf.hpp"
#include "misc/stop.hpp"
#include "rotateshift/rrr8.hpp"

InstructionDecoder::InstructionDecoder()
{
    InstantiateInstructions();
}

InstrPtr InstructionDecoder::DecodeInstruction(byte opcode)
{
    auto instruction = _instructions[opcode];
    instruction->Initialize(opcode);

    return instruction;
}

InstrPtr InstructionDecoder::DecodePrefixedInstruction(byte opcode)
{
    auto instruction = _prefixedInstructions[opcode];
    instruction->Initialize(opcode);

    return instruction;
}

InstrPtr InstructionDecoder::GetInterruptServiceRoutineInstruction(byte readyInterrupts)
{
    throw "Not implemented";
}
        
void InstructionDecoder::InstantiateInstructions()
{
    //unprefixed instructions
    for(byte opcode = 0x00; opcode < 0xFF; opcode++)
    {
        if ((opcode & 0xCF) == 0xC1)
            _instructions[opcode] = std::make_shared<POP>();
        else if ((opcode & 0xCF) == 0xC5)
            _instructions[opcode] = std::make_shared<PUSH>();

        else
        {
            switch(opcode)
            {
                case 0x00:
                    _instructions[opcode] = std::make_shared<NOP>();
                case 0x10:
                    _instructions[opcode] = std::make_shared<STOP>();
                case 0x27:
                    _instructions[opcode] = std::make_shared<DAA>();
                case 0x2F:
                    _instructions[opcode] = std::make_shared<CPL>();
                case 0x37:
                    _instructions[opcode] = std::make_shared<SCF>();
                case 0x76:
                    _instructions[opcode] = std::make_shared<HALT>();
                case 0xCB:
                    _instructions[opcode] = std::make_shared<PREFIX>();
                case 0xCD:
                    _instructions[opcode] = std::make_shared<CALL>();
                case 0x3F:
                    _instructions[opcode] = std::make_shared<CCF>();
                case 0xF3:
                    _instructions[opcode] = std::make_shared<DI>();
                case 0xFB:
                    _instructions[opcode] = std::make_shared<EI>();
            }        
        }       
    }

    //prefixed instructions
    for(byte opcode = 0x00; opcode < 0xFF; opcode++)
    {
        if ((opcode & 0xC0) == 0x40 && (opcode & 0x07) != 0x06)
            _prefixedInstructions[opcode] = std::make_shared<BITNR8>();

        if ((opcode & 0xC0) == 0xC0 && (opcode & 0x07) != 0x06)
            _prefixedInstructions[opcode] = std::make_shared<SETNR8>();

        else if ((opcode & 0xC0) == 0x80 && (opcode & 0x07) != 0x06)
            _prefixedInstructions[opcode] = std::make_shared<RESNR8>();

        else if ((opcode & 0xC0) == 0x40 && (opcode & 0x07) == 0x06)
            _prefixedInstructions[opcode] = std::make_shared<BITN_HL_>();

        else if ((opcode & 0xC0) == 0x80 && (opcode & 0x07) == 0x06)
            _prefixedInstructions[opcode] = std::make_shared<RESN_HL_>();

        else if ((opcode & 0xC0) == 0xC0 && (opcode & 0x07) == 0x06)
            _prefixedInstructions[opcode] = std::make_shared<SETN_HL_>();

        else if ((opcode & 0xF8) == 0x18 && opcode != 0x1E)
            _prefixedInstructions[opcode] = std::make_shared<RRR8>();            

        else
        {
            switch(opcode)
            {
                case 0xCD:
                    //_prefixedInstructions[opcode] = std::make_shared<CALL>();
                    break;
            }   
        }            
    }
}