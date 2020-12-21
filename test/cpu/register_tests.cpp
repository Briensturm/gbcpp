#include "test.hpp"

#include "cpu/reg_16bit.hpp"
#include "cpu/cpu_registers.hpp"

TEST_FIXTURE_BEGIN("CpuRegisters_Tests")
{
    TEST("Assigning_to_Reg16Bit_assigns_high_and_low_nibble")
    {
        uint8_t high, low;
        auto reg = Reg16Bit(high, low);

        reg = 0x1234;

        ASSERT_EQUAL<uint8_t>(0x12, high);
        ASSERT_EQUAL<uint8_t>(0x34, low);
    }

    TEST("Assigning_to_nibbles_updates_the_Reg16Bit")
    {
        uint8_t high, low;
        auto reg = Reg16Bit(high, low);

        high = 0x12;
        low = 0x34;

        ASSERT_EQUAL<unsigned short>(0x1234, reg);
    }

    TEST("Assigning_to_Reg8Bit_assigns_low_nibble")
    {
        uint8_t low;
        auto reg = Reg8Bit(low);

        reg = 0x1234;

        ASSERT_EQUAL<uint8_t>(0x34, low);
    }

    TEST("Assigning_to_low_nibble_updates_the_Reg8Bit")
    {
        uint8_t low;
        auto reg = Reg8Bit(low);

        low = 0x34;

        ASSERT_EQUAL<unsigned short>(0x34, reg);
    }

    TEST("Reg8Bit_behaves_like_8_bits_through_Reg16Bit_pointer")
    {
        uint8_t low;
        auto reg8 = std::make_shared<Reg8Bit>(Reg8Bit(low));
        auto reg16 = std::static_pointer_cast<Reg16Bit>(reg8);

        *reg16 = 0x1234;

        ASSERT_EQUAL<unsigned short>(0x34, *reg16);
    }

    TEST("Assigning_16bit_register_BC_sets_the_individual_registers")
    {
        auto registers = CpuRegisters();

        registers.BC = 0x1234;

        ASSERT_EQUAL<unsigned short>(0x12, registers.B);
        ASSERT_EQUAL<unsigned short>(0x34, registers.C);
    }

    TEST("Assigning_16bit_register_DE_sets_the_individual_registers")
    {
        auto registers = CpuRegisters();

        registers.DE = 0x1234;

        ASSERT_EQUAL<unsigned short>(0x12, registers.D);
        ASSERT_EQUAL<unsigned short>(0x34, registers.E);
    }

    TEST("Assigning_16bit_register_HL_sets_the_individual_registers")
    {
        auto registers = CpuRegisters();

        registers.HL = 0x1234;

        ASSERT_EQUAL<unsigned short>(0x12, registers.H);
        ASSERT_EQUAL<unsigned short>(0x34, registers.L);
    }

    TEST("Assigning_the_flag_register_assigns_the_corresponding_flags")
    {
        auto registers = CpuRegisters();

        registers.F = 0xFF;

        ASSERT_TRUE(registers.CarryFlag);
        ASSERT_TRUE(registers.HalfCarryFlag);
        ASSERT_TRUE(registers.ZeroFlag);
        ASSERT_TRUE(registers.SubtractionFlag);
    }

    TEST("Reading_at_out_of_range_index_throws_out_of_range_exception")
    {
        auto registers = CpuRegisters();

        ASSERT_THROWS<std::out_of_range>([&registers](){ registers.ReadRegister(8); });
    }

    TEST("Writing_at_out_of_range_index_throws_out_of_range_exception")
    {
        auto registers = CpuRegisters();

        ASSERT_THROWS<std::out_of_range>([&registers](){ registers.WriteRegister(8, 0x00); });
    }

    TEST("Resetting_CpuRegisters_sets_carry_flag")
    {
        auto registers = CpuRegisters();

        registers.Reset();

        ASSERT_TRUE(registers.CarryFlag);
    }

    TEST("Resetting_CpuRegisters_sets_half_carry_flag")
    {
        auto registers = CpuRegisters();

        registers.Reset();

        ASSERT_TRUE(registers.HalfCarryFlag);
    }

    TEST("Resetting_CpuRegisters_sets_zero_flag")
    {
        auto registers = CpuRegisters();

        registers.Reset();

        ASSERT_TRUE(registers.ZeroFlag);
    }

    TEST("Resetting_CpuRegisters_clears_subtraction_flag")
    {
        auto registers = CpuRegisters();

        registers.Reset();

        ASSERT_FALSE(registers.SubtractionFlag);
    }

    TEST("Resetting_CpuRegisters_sets_register_A_to_0x01")
    {
        auto registers = CpuRegisters();

        registers.Reset();

        ASSERT_EQUAL<unsigned short>(0x01, registers.A);
    }

    TEST("Resetting_CpuRegisters_sets_register_B_to_0x00")
    {
        auto registers = CpuRegisters();

        registers.Reset();

        ASSERT_EQUAL<unsigned short>(0x00, registers.B);
    }

    TEST("Resetting_CpuRegisters_sets_register_C_to_0x13")
    {
        auto registers = CpuRegisters();

        registers.Reset();

        ASSERT_EQUAL<unsigned short>(0x13, registers.C);
    }

    TEST("Resetting_CpuRegisters_sets_register_D_to_0x00")
    {
        auto registers = CpuRegisters();

        registers.Reset();

        ASSERT_EQUAL<unsigned short>(0x00, registers.D);
    }

    TEST("Resetting_CpuRegisters_sets_register_E_to_0xD8")
    {
        auto registers = CpuRegisters();

        registers.Reset();

        ASSERT_EQUAL<unsigned short>(0xD8, registers.E);
    }

    TEST("Resetting_CpuRegisters_sets_register_H_to_0x01")
    {
        auto registers = CpuRegisters();

        registers.Reset();

        ASSERT_EQUAL<unsigned short>(0x01, registers.H);
    }

    TEST("Resetting_CpuRegisters_sets_register_L_to_0x4D")
    {
        auto registers = CpuRegisters();

        registers.Reset();

        ASSERT_EQUAL<unsigned short>(0x4D, registers.L);
    }
}
TEST_FIXTURE_END