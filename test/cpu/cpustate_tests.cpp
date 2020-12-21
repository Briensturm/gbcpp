#include "test.hpp"
#include "mocks/registers_mock.hpp"

#include "cpu/cpu_state.hpp"

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

        VERIFY_INVOKE_COUNT(registersMock, Reset, 1);        
    }
}
TEST_FIXTURE_END