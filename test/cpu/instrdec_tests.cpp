#include "test.hpp"

#include "cpu/instructions/instruction_decoder.hpp"

TEST_FIXTURE_BEGIN("InstructionDecoder_Tests")
{
    TEST("Creating_an_InstructionDecoder_does_not_throw_an_exception")
    {
        ASSERT_DOES_NOT_THROW([](){ auto instrDec = InstructionDecoder(); });
    }
    
    TEST("All_non_forbidden_non_prefixed_instructions_are_implemented")
    {
        auto instrDec = InstructionDecoder();

        for (ushort opcode = 0x00; opcode <= 0xFF; opcode++)
        {
            if (opcode == 0xD3 || opcode == 0xE3 || opcode == 0xE4 || opcode == 0xF4
                || opcode == 0xDB || opcode == 0xEB || opcode == 0xEC || opcode == 0xFC
                || opcode == 0xDD || opcode == 0xED || opcode == 0xFD)
                continue;

            ASSERT_DOES_NOT_THROW([&instrDec, opcode](){ instrDec.DecodeInstruction((byte)opcode); });
        }
    }

    TEST("All_prefixed_instructions_are_implemented")
    {
        auto instrDec = InstructionDecoder();
        
        for (ushort opcode = 0x00; opcode <= 0xFF; opcode++)
        {
            ASSERT_DOES_NOT_THROW([&instrDec, opcode](){ instrDec.DecodePrefixedInstruction((byte)opcode); });
        }
    }    
}
TEST_FIXTURE_END