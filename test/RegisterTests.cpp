#include "Test.hpp"

#include "Reg16Bit.hpp"
#include "CpuRegisters.hpp"

TEST_FIXTURE_BEGIN("RegisterTests")
{
    TEST("Assigning_to_Reg16Bit_assigns_high_and_low_nibble")
    {
        int8_t high, low;
        auto reg = Reg16Bit(high, low);

        reg = 0x1234;

        ASSERT_EQUAL<uint8_t>(0x12, high);
        ASSERT_EQUAL<uint8_t>(0x34, low);
    }

    TEST("Assigning_to_nibbles_updates_the_Reg16Bit")
    {
        int8_t high, low;
        auto reg = Reg16Bit(high, low);

        high = 0x12;
        low = 0x34;

        ASSERT_EQUAL<unsigned short>(0x1234, reg);
    }

    TEST("Assigning_to_Reg8Bit_assigns_low_nibble")
    {
        int8_t low;
        auto reg = Reg8Bit(low);

        reg = 0x1234;

        ASSERT_EQUAL<uint8_t>(0x34, low);
    }

    TEST("Assigning_to_low_nibble_updates_the_Reg8Bit")
    {
        int8_t low;
        auto reg = Reg8Bit(low);

        low = 0x34;

        ASSERT_EQUAL<unsigned short>(0x34, reg);
    }

    TEST("Reg8Bit_behaves_like_8_bits_through_Reg16Bit_pointer")
    {
        int8_t low;
        auto reg8 = std::make_shared<Reg8Bit>(Reg8Bit(low));
        auto reg16 = std::static_pointer_cast<Reg16Bit>(reg8);

        *reg16 = 0x1234;

        ASSERT_EQUAL<unsigned short>(0x34, *reg16);
    }

    TEST("Assigning_register_A_updates_the_register_value")
    {
        auto registers = CpuRegisters();

        registers.A = 0x42;

        ASSERT_EQUAL<unsigned short>(0x42, registers.A);
    }

    TEST("Assigning_register_B_updates_the_register_value")
    {
        auto registers = CpuRegisters();

        registers.B = 0x42;

        ASSERT_EQUAL<unsigned short>(0x42, registers.B);
    }

    TEST("Assigning_register_C_updates_the_register_value")
    {
        auto registers = CpuRegisters();

        registers.C = 0x42;

        ASSERT_EQUAL<unsigned short>(0x42, registers.C);
    }

    TEST("Assigning_register_D_updates_the_register_value")
    {
        auto registers = CpuRegisters();

        registers.D = 0x42;

        ASSERT_EQUAL<unsigned short>(0x42, registers.D);
    }

    TEST("Assigning_register_E_updates_the_register_value")
    {
        auto registers = CpuRegisters();

        registers.E = 0x42;

        ASSERT_EQUAL<unsigned short>(0x42, registers.E);
    }

    TEST("Assigning_register_H_updates_the_register_value")
    {
        auto registers = CpuRegisters();

        registers.H = 0x42;

        ASSERT_EQUAL<unsigned short>(0x42, registers.H);
    }

    TEST("Assigning_register_L_updates_the_register_value")
    {
        auto registers = CpuRegisters();

        registers.L = 0x42;

        ASSERT_EQUAL<unsigned short>(0x42, registers.L);
    }

    TEST("Assigning_register_HL_updates_the_register_value")
    {
        auto registers = CpuRegisters();

        registers.HL = 0x1234;

        ASSERT_EQUAL<unsigned short>(0x1234, registers.HL);
    }

    TEST("Reading_at_out_of_range_index_throws_out_of_range_exception")
    {
        auto registers = CpuRegisters();

        ASSERT_THROWS(std::out_of_range, registers.ReadRegister(8));
    }

    TEST("Writing_at_out_of_range_index_throws_out_of_range_exception")
    {
        auto registers = CpuRegisters();

        ASSERT_THROWS(std::out_of_range, registers.WriteRegister(8, 0x00));
    }

    TEST("")
    {
        
    }
} 
TEST_FIXTURE_END