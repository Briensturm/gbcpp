#include "test.hpp"
#include "mocks/registers_mock.hpp"

#include "cpu/cpu_state.hpp"

CpuState CreateCpuState()
{
    auto registersMock = CREATE_MOCK<CpuRegistersMock>();
    auto registers = GET_OBJECT<CpuRegisters>(registersMock);
    return CpuState(registers);
}

TEST_FIXTURE_BEGIN("CpuState_Tests")
{
    TEST("Creating_a_CpuState_without_passing_a_CpuRegisters_object_throws_invalid_argument_exception")
    {
        ASSERT_THROWS<std::invalid_argument>([](){ CpuState(nullptr); });
    }

    TEST("Creating_a_CpuState_with_a_CpuRegisters_object_does_not_throw")
    {
        auto registersMock = CREATE_MOCK<CpuRegistersMock>();
        auto registers = GET_OBJECT<CpuRegisters>(registersMock);

        ASSERT_DOES_NOT_THROW([&registers](){ auto cpuState = CpuState(registers); });
    }

    TEST("Resetting_a_CpuState_object_resets_its_CpuRegisters_object")
    {
        auto registersMock = CREATE_MOCK<CpuRegistersMock>();
        auto registers = GET_OBJECT<CpuRegisters>(registersMock);
        auto cpuState = CpuState(registers);

        cpuState.Reset();

        ASSERT_EQUAL(1, registersMock->void_Reset_InvokeCount);        
    }

    TEST("Resetting_CpuState_clears_InterruptMasterEnable")
    {
        auto cpuState = CreateCpuState();
        cpuState.InterruptMasterEnable = true;

        cpuState.Reset();

        ASSERT_FALSE(cpuState.InterruptMasterEnable);
    }

    TEST("Resetting_CpuState_clears_InstructionPrefix")
    {
        auto cpuState = CreateCpuState();
        cpuState.InstructionPrefix = true;

        cpuState.Reset();

        ASSERT_FALSE(cpuState.InstructionPrefix);
    }

    TEST("Resetting_CpuState_clears_HaltMode")
    {
        auto cpuState = CreateCpuState();
        cpuState.HaltMode = true;

        cpuState.Reset();

        ASSERT_FALSE(cpuState.HaltMode);
    }

    TEST("Resetting_CpuState_clears_HaltBug")
    {
        auto cpuState = CreateCpuState();
        cpuState.HaltBug = true;

        cpuState.Reset();

        ASSERT_FALSE(cpuState.HaltBug);
    }

    TEST("Resetting_CpuState_clears_StopMode")
    {
        auto cpuState = CreateCpuState();
        cpuState.StopMode = true;

        cpuState.Reset();

        ASSERT_FALSE(cpuState.StopMode);
    }

    TEST("Resetting_CpuState_clears_ImeScheduled")
    {
        auto cpuState = CreateCpuState();
        cpuState.ImeScheduled = true;

        cpuState.Reset();

        ASSERT_FALSE(cpuState.ImeScheduled);
    }

    TEST("Resetting_CpuState_sets_StackPointer_to_0xFFFE")
    {
        auto cpuState = CreateCpuState();
        cpuState.StackPointer = 0x0000;

        cpuState.Reset();

        ASSERT_EQUAL<ushort>(0xFFFE, cpuState.StackPointer);
    }
}
TEST_FIXTURE_END