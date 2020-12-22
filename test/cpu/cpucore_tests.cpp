#include "test.hpp"
#include "mocks/ram_mock.hpp"
#include "mocks/cpustate_mock.hpp"
#include "mocks/instrdec_mock.hpp"
#include "mocks/instr_mock.hpp"

#include "cpu/cpu_core.hpp"

CpuCorePtr CreateCpuCore(std::shared_ptr<CpuState>& outCpuState)
{
    outCpuState = std::make_shared<CpuState>(CpuState(MOCK_OF<CpuRegistersMock, CpuRegisters>()));

    auto ramMock = CREATE_MOCK<RamMock>();
    ramMock->byte_ReadByte_ushort_SetReturnValue(0x0100, 0x00);

    auto instrMock = CREATE_MOCK<InstrMock>();
    instrMock->int_GetInstructionLength_SetReturnValue(2);
    instrMock->Initialize(0x00);

    auto instrdecMock = CREATE_MOCK<InstrDecMock>();
    instrdecMock->InstrPtr_DecodeInstruction_byte_SetReturnValue(0x00, GET_OBJECT<Instruction>(instrMock));        
    
    auto cpuCore =  std::make_shared<CpuCore>(GET_OBJECT<RandomAccessMemory>(ramMock), 
                                              outCpuState,
                                              GET_OBJECT<InstructionDecoder>(instrdecMock));        

    cpuCore->Reset();
    return cpuCore;
}

TEST_FIXTURE_BEGIN("CpuCore_Tests")
{
    TEST("Creating_a_CpuCore_without_passing_a_ram_object_throws_invalid_argument_exception")
    {
        ASSERT_THROWS<std::invalid_argument>([](){ CpuCore(nullptr, 
                                                           MOCK_OF<CpuStateMock, CpuState>(), 
                                                           MOCK_OF<InstrDecMock, InstructionDecoder>()); });
    }

    TEST("Creating_a_CpuCore_without_passing_a_CpuState_object_throws_invalid_argument_exception")
    {
        ASSERT_THROWS<std::invalid_argument>([](){ CpuCore(MOCK_OF<RamMock, RandomAccessMemory>(), 
                                                           nullptr, 
                                                           MOCK_OF<InstrDecMock, InstructionDecoder>()); });
    }

    TEST("Creating_a_CpuCore_without_passing_an_InstructionDecoder_object_throws_invalid_argument_exception")
    {
        ASSERT_THROWS<std::invalid_argument>([](){ CpuCore(MOCK_OF<RamMock, RandomAccessMemory>(), 
                                                           MOCK_OF<CpuStateMock, CpuState>(), 
                                                           nullptr); });
    }

    TEST("Creating_a_CpuCore_while_passing_its_dependencies_does_not_throw")
    {
        ASSERT_DOES_NOT_THROW([](){ CpuCore(MOCK_OF<RamMock, RandomAccessMemory>(), 
                                            MOCK_OF<CpuStateMock, CpuState>(), 
                                            MOCK_OF<InstrDecMock, InstructionDecoder>()); });
    }

    TEST("Resetting_CpuCore_resets_its_CpuState")
    {
        auto cpuStateMock = CREATE_MOCK<CpuStateMock>();
        auto cpuState = GET_OBJECT<CpuState>(cpuStateMock);
        auto cpuCore =  CpuCore(MOCK_OF<RamMock, RandomAccessMemory>(), 
                                cpuState, 
                                MOCK_OF<InstrDecMock, InstructionDecoder>());

        cpuCore.Reset();

        VERIFY(cpuStateMock, Reset, ONCE);
    }

    TEST("AdvanceMachineCycle_handles_ImeScheduled_with_one_cycle_delay")
    {
        std::shared_ptr<CpuState> cpuState;
        auto cpuCore = CreateCpuCore(cpuState);

        cpuCore->Reset();
        cpuState->ImeScheduled = true;
        cpuState->InterruptMasterEnable = false;

        cpuCore->AdvanceMachineCycle();

        ASSERT_TRUE(cpuState->InterruptMasterEnable);
        ASSERT_FALSE(cpuState->ImeScheduled);
    }
}
TEST_FIXTURE_END