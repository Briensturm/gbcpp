#include "test.hpp"
#include "mocks/ram_mock.hpp"
#include "mocks/cpustate_mock.hpp"
#include "mocks/instrdec_mock.hpp"
#include "mocks/instr_mock.hpp"

#include "cpu/cpu_core.hpp"

CpuCorePtr CreateCpuCore(CpuStatePtr& outCpuState, InstrPtr& outInstr, InstrDecPtr& outInstrdec, RamPtr& outRam)
{
    outCpuState = std::make_shared<CpuState>(CpuState(MOCK_OF<CpuRegistersMock, CpuRegisters>()));

    auto ramMock = CREATE_MOCK<RamMock>();
    ramMock->byte_ReadByte_ushort_SetReturnValue(0x0100, 0x00);
    ramMock->byte_ReadByte_ushort_SetReturnValue(0x0101, 0x00);
    ramMock->byte_ReadByte_ushort_SetReturnValue(constants::reg::int_flags, 0x00);
    outRam = GET_OBJECT<RandomAccessMemory>(ramMock);

    auto instrMock = CREATE_MOCK<InstrMock>();
    instrMock->int_GetInstructionLength_SetReturnValue(1);
    instrMock->Initialize(0x00);
    outInstr = GET_OBJECT<Instruction>(instrMock);

    auto instrdecMock = CREATE_MOCK<InstrDecMock>();
    instrdecMock->InstrPtr_DecodeInstruction_byte_SetReturnValue(0x00, GET_OBJECT<Instruction>(instrMock)); 
    outInstrdec = GET_OBJECT<InstructionDecoder>(instrdecMock);    
    
    auto cpuCore =  std::make_shared<CpuCore>(GET_OBJECT<RandomAccessMemory>(ramMock), 
                                              outCpuState,
                                              GET_OBJECT<InstructionDecoder>(instrdecMock));        

    cpuCore->Reset();
    return cpuCore;
}

CpuCorePtr CreateCpuCore(CpuStatePtr& outCpuState, RamPtr& outRam)
{
    InstrPtr instr;
    InstrDecPtr instrDec;
    return CreateCpuCore(outCpuState, instr, instrDec, outRam);
}

CpuCorePtr CreateCpuCore(CpuStatePtr& outCpuState, InstrDecPtr& outInstrdec)
{
    InstrPtr instr;
    RamPtr ram;
    return CreateCpuCore(outCpuState, instr, outInstrdec, ram);
}

CpuCorePtr CreateCpuCore(CpuStatePtr& outCpuState, InstrPtr& outInstr)
{
    InstrDecPtr instrDec;
    RamPtr ram;
    return CreateCpuCore(outCpuState, outInstr, instrDec, ram);
}

CpuCorePtr CreateCpuCore(CpuStatePtr& outCpuState)
{
    InstrPtr instr;
    return CreateCpuCore(outCpuState, instr);
}

CpuCorePtr CreateCpuCore()
{
    CpuStatePtr cpuState;
    return CreateCpuCore(cpuState);
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

    TEST("AdvanceMachineCycle_executes_cycle_of_instruction_if_not_in_halt_or_stop")
    {
        CpuStatePtr cpuState;
        InstrPtr instr;
        auto cpuCore = CreateCpuCore(cpuState, instr);

        cpuCore->Reset();
        cpuCore->AdvanceMachineCycle();

        ASSERT_EQUAL(1, GET_MOCK<InstrMock>(instr)->ExecuteCycleCalled);
    }

    TEST("AdvanceMachineCycle_does_not_execute_cycle_of_instruction_if_in_halt")
    {
        CpuStatePtr cpuState;
        InstrPtr instr;
        auto cpuCore = CreateCpuCore(cpuState, instr);

        cpuCore->Reset();
        cpuState->HaltMode = true;

        cpuCore->AdvanceMachineCycle();

        ASSERT_EQUAL(0, GET_MOCK<InstrMock>(instr)->ExecuteCycleCalled);
    }

    TEST("AdvanceMachineCycle_does_not_execute_cycle_of_instruction_if_in_stop")
    {
        CpuStatePtr cpuState;
        InstrPtr instr;
        auto cpuCore = CreateCpuCore(cpuState, instr);

        cpuCore->Reset();
        cpuState->StopMode = true;
        
        cpuCore->AdvanceMachineCycle();

        ASSERT_EQUAL(0, GET_MOCK<InstrMock>(instr)->ExecuteCycleCalled);
    }

    TEST("AdvanceMachineCycle_fetches_next_instruction_once_all_cycles_of_current_instr_are_done")
    {
        CpuStatePtr cpuState;
        InstrDecPtr instrDec;
        auto cpuCore = CreateCpuCore(cpuState, instrDec);

        cpuCore->Reset();        
        cpuCore->AdvanceMachineCycle();

        VERIFY_RET_P(GET_MOCK<InstrDecMock>(instrDec), InstrPtr, DecodeInstruction, byte, 0x00, TIMES(2));
    }
}
TEST_FIXTURE_END