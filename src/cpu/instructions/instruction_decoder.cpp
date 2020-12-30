#include "instruction_decoder.hpp"

#include "arithmetic/adca_hl_.hpp"
#include "arithmetic/adcad8.hpp"
#include "arithmetic/adcar8.hpp"
#include "arithmetic/adda_hl_.hpp"
#include "arithmetic/addad8.hpp"
#include "arithmetic/addar8.hpp"
#include "arithmetic/addhlr16.hpp"
#include "arithmetic/addsps8.hpp"
#include "arithmetic/cpa_hl_.hpp"
#include "arithmetic/cpad8.hpp"
#include "arithmetic/cpar8.hpp"
#include "arithmetic/dec_hl_.hpp"
#include "arithmetic/decr8.hpp"
#include "arithmetic/decr16.hpp"
#include "arithmetic/inc_hl_.hpp"
#include "arithmetic/incr8.hpp"
#include "arithmetic/incr16.hpp"
#include "arithmetic/sbca_hl_.hpp"
#include "arithmetic/sbcad8.hpp"
#include "arithmetic/sbcar8.hpp"
#include "arithmetic/suba_hl_.hpp"
#include "arithmetic/subad8.hpp"
#include "arithmetic/subar8.hpp"
#include "bit/bitn_hl_.hpp"
#include "bit/bitnr8.hpp"
#include "bit/resn_hl_.hpp"
#include "bit/resnr8.hpp"
#include "bit/setn_hl_.hpp"
#include "bit/setnr8.hpp"
#include "controlflow/call.hpp"
#include "controlflow/callcc.hpp"
#include "controlflow/jpcc.hpp"
#include "controlflow/jpd16.hpp"
#include "controlflow/jphl.hpp"
#include "controlflow/jr.hpp"
#include "controlflow/jrcc.hpp"
#include "controlflow/ret.hpp"
#include "controlflow/retcc.hpp"
#include "controlflow/reti.hpp"
#include "controlflow/rst.hpp"
#include "logic/anda_hl_.hpp"
#include "logic/andad8.hpp"
#include "logic/andar8.hpp"
#include "logic/ora_hl_.hpp"
#include "logic/orad8.hpp"
#include "logic/orar8.hpp"
#include "logic/xora_hl_.hpp"
#include "logic/xorad8.hpp"
#include "logic/xorar8.hpp"
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
    _ldisr = std::make_shared<LDISR>();
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
    _ldisr->Prepare(readyInterrupts);
    return _ldisr;
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

        else if ((opcode & 0xF8) == 0xA0 && opcode != 0xA6)
            _instructions[opcode] = std::make_shared<ANDAR8>();

        else if ((opcode & 0xF8) == 0xB0 && opcode != 0xB6)
            _instructions[opcode] = std::make_shared<ORAR8>();

        else if ((opcode & 0xF8) == 0xA8 && opcode != 0xAE)
            _instructions[opcode] = std::make_shared<XORAR8>();

        else if ((opcode & 0xE7) == 0xC4)
            _instructions[opcode] = std::make_shared<CALLCC>();

        else if ((opcode & 0xE7) == 0xC2)
            _instructions[opcode] = std::make_shared<JPCC>();

        else if ((opcode & 0xE7) == 0x20)
            _instructions[opcode] = std::make_shared<JRCC>();

        else if ((opcode & 0xE7) == 0xC0)
            _instructions[opcode] = std::make_shared<RETCC>();

        else if ((opcode & 0xC7) == 0xC7)  
            _instructions[opcode] = std::make_shared<RST>(); 

        else if ((opcode & 0xF8) == 0x88 && opcode != 0x8E)
            _instructions[opcode] = std::make_shared<ADCAR8>();

        else if ((opcode & 0xF8) == 0x80 && opcode != 0x86)
            _instructions[opcode] = std::make_shared<ADDAR8>();

        else if ((opcode & 0xCF) == 0x09)
            _instructions[opcode] = std::make_shared<ADDHLR16>();

        else if ((opcode & 0xF8) == 0xB8 && opcode != 0xBE)
            _instructions[opcode] = std::make_shared<CPAR8>();

        else if ((opcode & 0xC7) == 0x05 && (opcode & 0x38) != 0x30)
            _instructions[opcode] = std::make_shared<DECR8>();
            
        else if ((opcode & 0xCF) == 0x0B)
            _instructions[opcode] = std::make_shared<DECR16>();

        else if ((opcode & 0xC7) == 0x04 && (opcode & 0x38) != 0x30)
            _instructions[opcode] = std::make_shared<INCR8>();

        else if ((opcode & 0xCF) == 0x03)
            _instructions[opcode] = std::make_shared<INCR16>();

        else if ((opcode & 0xF8) == 0x98 && opcode != 0x9E)
            _instructions[opcode] = std::make_shared<SBCAR8>();

        else if ((opcode & 0xF8) == 0x90 && opcode != 0x96)
            _instructions[opcode] = std::make_shared<SUBAR8>();

        else
        {
            switch(opcode)
            {
                case 0x00:
                    _instructions[opcode] = std::make_shared<NOP>();
                case 0x10:
                    _instructions[opcode] = std::make_shared<STOP>();
                case 0x18:
                    _instructions[opcode] = std::make_shared<JR>();
                case 0x27:
                    _instructions[opcode] = std::make_shared<DAA>();
                case 0x2F:
                    _instructions[opcode] = std::make_shared<CPL>();
                case 0x34:
                    _instructions[opcode] = std::make_shared<INC_HL_>();
                case 0x35:
                    _instructions[opcode] = std::make_shared<DEC_HL_>();
                case 0x37:
                    _instructions[opcode] = std::make_shared<SCF>();
                case 0x3F:
                    _instructions[opcode] = std::make_shared<CCF>();
                case 0x76:
                    _instructions[opcode] = std::make_shared<HALT>();
                case 0x86:
                    _instructions[opcode] = std::make_shared<ADDA_HL_>();
                case 0x8E:
                    _instructions[opcode] = std::make_shared<ADCA_HL_>();
                case 0x96:
                    _instructions[opcode] = std::make_shared<SUBA_HL_>();
                case 0x9E:
                    _instructions[opcode] = std::make_shared<SBCA_HL_>();
                case 0xA6:
                    _instructions[opcode] = std::make_shared<ANDA_HL_>();
                case 0xAE:
                    _instructions[opcode] = std::make_shared<XORA_HL_>();
                case 0xB6:
                    _instructions[opcode] = std::make_shared<ORA_HL_>();
                case 0xBE:
                    _instructions[opcode] = std::make_shared<CPA_HL_>();
                case 0xC3:
                    _instructions[opcode] = std::make_shared<JPD16>();
                case 0xC6:
                    _instructions[opcode] = std::make_shared<ADDAD8>();
                case 0xC9:
                    _instructions[opcode] = std::make_shared<RET>();
                case 0xCB:
                    _instructions[opcode] = std::make_shared<PREFIX>();
                case 0xCD:
                    _instructions[opcode] = std::make_shared<CALL>(); 
                case 0xCE:
                    _instructions[opcode] = std::make_shared<ADCAD8>();
                case 0xD6:
                    _instructions[opcode] = std::make_shared<SUBAD8>();
                case 0xD9:
                    _instructions[opcode] = std::make_shared<RETI>();
                case 0xDE:
                    _instructions[opcode] = std::make_shared<SBCAD8>();
                case 0xE6:
                    _instructions[opcode] = std::make_shared<ANDAD8>();
                case 0xE8:
                    _instructions[opcode] = std::make_shared<ADDSPS8>();
                case 0xE9:
                    _instructions[opcode] = std::make_shared<JPHL>();
                case 0xEE:
                    _instructions[opcode] = std::make_shared<XORAD8>();
                case 0xF3:
                    _instructions[opcode] = std::make_shared<DI>();
                case 0xF6:
                    _instructions[opcode] = std::make_shared<ORAD8>();
                case 0xFB:
                    _instructions[opcode] = std::make_shared<EI>();
                case 0xFE:
                    _instructions[opcode] = std::make_shared<CPAD8>();
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