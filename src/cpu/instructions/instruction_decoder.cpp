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
#include "load/ld_bc_a.hpp"
#include "load/ld_d16_a.hpp"
#include "load/ld_d16_sp.hpp"
#include "load/ld_de_a.hpp"
#include "load/ld_hl_d8.hpp"
#include "load/ld_hl_r8.hpp"
#include "load/ld_hlm_a.hpp"
#include "load/ld_hlp_a.hpp"
#include "load/lda_bc_.hpp"
#include "load/lda_d16_.hpp"
#include "load/lda_de_.hpp"
#include "load/lda_hlm_.hpp"
#include "load/lda_hlp_.hpp"
#include "load/ldh_c_a.hpp"
#include "load/ldh_d8_a.hpp"
#include "load/ldha_c_.hpp"
#include "load/ldha_d8_.hpp"
#include "load/ldhlsps8.hpp"
#include "load/ldr8_hl_.hpp"
#include "load/ldr8d8.hpp"
#include "load/ldr8r8.hpp"
#include "load/ldr16d16.hpp"
#include "load/ldsphl.hpp"
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
#include "rotateshift/rl_hl_.hpp"
#include "rotateshift/rla.hpp"
#include "rotateshift/rlc_hl_.hpp"
#include "rotateshift/rlca.hpp"
#include "rotateshift/rlcr8.hpp"
#include "rotateshift/rlr8.hpp"
#include "rotateshift/rr_hl_.hpp"
#include "rotateshift/rra.hpp"
#include "rotateshift/rrc_hl_.hpp"
#include "rotateshift/rrca.hpp"
#include "rotateshift/rrcr8.hpp"
#include "rotateshift/rrr8.hpp"
#include "rotateshift/sla_hl_.hpp"
#include "rotateshift/slar8.hpp"
#include "rotateshift/sra_hl_.hpp"
#include "rotateshift/srar8.hpp"
#include "rotateshift/srl_hl_.hpp"
#include "rotateshift/srlr8.hpp"
#include "rotateshift/swap_hl_.hpp"
#include "rotateshift/swapr8.hpp"

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
    for(ushort opcode = 0x00; opcode <= 0xFF; opcode++)
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

        else if ((opcode & 0xF8) == 0x70 && opcode != 0x76)
            _instructions[opcode] = std::make_shared<LD_HL_R8>();

        else if ((opcode & 0xC7) == 0x46 && opcode != 0x76)
            _instructions[opcode] = std::make_shared<LDR8_HL_>();

        else if ((opcode & 0xC7) == 0x06 && opcode != 0x36)
            _instructions[opcode] = std::make_shared<LDR8D8>();

        else if ((opcode >> 6) == 0x01 && (opcode & 0x07) != 0x06 && (opcode & 0x38) != 0x30)
            _instructions[opcode] = std::make_shared<LDR8R8>();

        else if ((opcode & 0xCF) == 0x01)
            _instructions[opcode] = std::make_shared<LDR16D16>();


        else
        {
            switch(opcode)
            {
                case 0x00:
                    _instructions[opcode] = std::make_shared<NOP>();
                    continue;
                case 0x02:
                    _instructions[opcode] = std::make_shared<LD_BC_A>();
                    continue;
                case 0x07:
                    _instructions[opcode] = std::make_shared<RLCA>();
                    continue;
                case 0x08:
                    _instructions[opcode] = std::make_shared<LD_D16_SP>();
                    continue;
                case 0x0A:
                    _instructions[opcode] = std::make_shared<LDA_BC_>();
                    continue;
                case 0x0F:
                    _instructions[opcode] = std::make_shared<RRCA>();
                    continue;
                case 0x10:
                    _instructions[opcode] = std::make_shared<STOP>();
                    continue;
                case 0x12:
                    _instructions[opcode] = std::make_shared<LD_DE_A>();
                    continue;
                case 0x17:
                    _instructions[opcode] = std::make_shared<RLA>();
                    continue;
                case 0x18:
                    _instructions[opcode] = std::make_shared<JR>();
                    continue;
                case 0x1A:
                    _instructions[opcode] = std::make_shared<LDA_DE_>();
                    continue;
                case 0x1F:
                    _instructions[opcode] = std::make_shared<RRA>();
                    continue;
                case 0x22:
                    _instructions[opcode] = std::make_shared<LD_HLP_A>();
                    continue;
                case 0x27:
                    _instructions[opcode] = std::make_shared<DAA>();
                    continue;
                case 0x2A:
                    _instructions[opcode] = std::make_shared<LDA_HLP_>();
                    continue;
                case 0x2F:
                    _instructions[opcode] = std::make_shared<CPL>();
                    continue;
                case 0x32:
                    _instructions[opcode] = std::make_shared<LD_HLM_A>();
                    continue;
                case 0x34:
                    _instructions[opcode] = std::make_shared<INC_HL_>();
                    continue;
                case 0x35:
                    _instructions[opcode] = std::make_shared<DEC_HL_>();
                    continue;
                case 0x36:
                    _instructions[opcode] = std::make_shared<LD_HL_D8>();
                    continue;
                case 0x37:
                    _instructions[opcode] = std::make_shared<SCF>();
                    continue;
                case 0x3A:
                    _instructions[opcode] = std::make_shared<LDA_HLM_>();
                    continue;
                case 0x3F:
                    _instructions[opcode] = std::make_shared<CCF>();
                    continue;
                case 0x76:
                    _instructions[opcode] = std::make_shared<HALT>();
                    continue;
                case 0x86:
                    _instructions[opcode] = std::make_shared<ADDA_HL_>();
                    continue;
                case 0x8E:
                    _instructions[opcode] = std::make_shared<ADCA_HL_>();
                    continue;
                case 0x96:
                    _instructions[opcode] = std::make_shared<SUBA_HL_>();
                    continue;
                case 0x9E:
                    _instructions[opcode] = std::make_shared<SBCA_HL_>();
                    continue;
                case 0xA6:
                    _instructions[opcode] = std::make_shared<ANDA_HL_>();
                    continue;
                case 0xAE:
                    _instructions[opcode] = std::make_shared<XORA_HL_>();
                    continue;
                case 0xB6:
                    _instructions[opcode] = std::make_shared<ORA_HL_>();
                    continue;
                case 0xBE:
                    _instructions[opcode] = std::make_shared<CPA_HL_>();
                    continue;
                case 0xC3:
                    _instructions[opcode] = std::make_shared<JPD16>();
                    continue;
                case 0xC6:
                    _instructions[opcode] = std::make_shared<ADDAD8>();
                    continue;
                case 0xC9:
                    _instructions[opcode] = std::make_shared<RET>();
                    continue;
                case 0xCB:
                    _instructions[opcode] = std::make_shared<PREFIX>();
                    continue;
                case 0xCD:
                    _instructions[opcode] = std::make_shared<CALL>(); 
                    continue;
                case 0xCE:
                    _instructions[opcode] = std::make_shared<ADCAD8>();
                    continue;
                case 0xD6:
                    _instructions[opcode] = std::make_shared<SUBAD8>();
                    continue;
                case 0xD9:
                    _instructions[opcode] = std::make_shared<RETI>();
                    continue;
                case 0xDE:
                    _instructions[opcode] = std::make_shared<SBCAD8>();
                    continue;
                case 0xE0:
                    _instructions[opcode] = std::make_shared<LDH_D8_A>();
                    continue;
                case 0xE2:
                    _instructions[opcode] = std::make_shared<LDH_C_A>();
                    continue;
                case 0xE6:
                    _instructions[opcode] = std::make_shared<ANDAD8>();
                    continue;
                case 0xE8:
                    _instructions[opcode] = std::make_shared<ADDSPS8>();
                    continue;
                case 0xE9:
                    _instructions[opcode] = std::make_shared<JPHL>();
                    continue;
                case 0xEA:
                    _instructions[opcode] = std::make_shared<LD_D16_A>();
                    continue;
                case 0xEE:
                    _instructions[opcode] = std::make_shared<XORAD8>();
                    continue;
                case 0xF0:
                    _instructions[opcode] = std::make_shared<LDHA_D8_>();
                    continue;
                case 0xF2:
                    _instructions[opcode] = std::make_shared<LDHA_C_>();
                    continue;
                case 0xF3:
                    _instructions[opcode] = std::make_shared<DI>();
                    continue;
                case 0xF6:
                    _instructions[opcode] = std::make_shared<ORAD8>();
                    continue;
                case 0xF8:
                    _instructions[opcode] = std::make_shared<LDHLSPS8>();
                    continue;
                case 0xF9:
                    _instructions[opcode] = std::make_shared<LDSPHL>();
                    continue;
                case 0xFA:
                    _instructions[opcode] = std::make_shared<LDA_D16_>();
                    continue;
                case 0xFB:
                    _instructions[opcode] = std::make_shared<EI>();
                    continue;
                case 0xFE:
                    _instructions[opcode] = std::make_shared<CPAD8>();
                    continue;
            }        
        }       
    }

    //prefixed instructions
    for(ushort opcode = 0x00; opcode <= 0xFF; opcode++)
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

        else if ((opcode & 0xF8) == 0 && opcode != 0x06)
            _prefixedInstructions[opcode] = std::make_shared<RLCR8>(); 

        else if ((opcode & 0xF8) == 0x10 && opcode != 0x16)
            _prefixedInstructions[opcode] = std::make_shared<RLR8>(); 

        else if ((opcode & 0xF8) == 0x08 && opcode != 0x0E)
            _prefixedInstructions[opcode] = std::make_shared<RRCR8>(); 

        else if ((opcode & 0xF8) == 0x20 && opcode != 0x26)
            _prefixedInstructions[opcode] = std::make_shared<SLAR8>(); 

        else if ((opcode & 0xF8) == 0x28 && opcode != 0x2E)
            _prefixedInstructions[opcode] = std::make_shared<SRAR8>(); 

        else if ((opcode & 0xF8) == 0x38 && opcode != 0x3E)
            _prefixedInstructions[opcode] = std::make_shared<SRLR8>(); 

        else if ((opcode & 0xF8) == 0x30 && opcode != 0x36)
            _prefixedInstructions[opcode] = std::make_shared<SWAPR8>(); 

        else
        {
            switch(opcode)
            {
                case 0x06:
                    _prefixedInstructions[opcode] = std::make_shared<RLC_HL_>();
                    continue;
                case 0x0E:
                    _prefixedInstructions[opcode] = std::make_shared<RRC_HL_>();
                    continue;
                case 0x16:
                    _prefixedInstructions[opcode] = std::make_shared<RL_HL_>();
                    continue;
                case 0x1E:
                    _prefixedInstructions[opcode] = std::make_shared<RR_HL_>();
                    continue;
                case 0x26:
                    _prefixedInstructions[opcode] = std::make_shared<SLA_HL_>();
                    continue;
                case 0x2E:
                    _prefixedInstructions[opcode] = std::make_shared<SRA_HL_>();
                    continue;
                case 0x36:
                    _prefixedInstructions[opcode] = std::make_shared<SWAP_HL_>();
                    continue;
                case 0x3E:
                    _prefixedInstructions[opcode] = std::make_shared<SRL_HL_>();
                    continue;
            }   
        }            
    }
}