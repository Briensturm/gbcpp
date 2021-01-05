#include "test.hpp"
#include "mocks/delegate_mock.hpp"

#include <vector>

#include "ram/ram.hpp"

TEST_FIXTURE_BEGIN("RandomAccessMemory_Tests")
{
    TEST("Creating_a_RandomAccessMemory_does_not_throw_an_exception")
    {
        ASSERT_DOES_NOT_THROW([](){ auto ram = std::make_shared<RandomAccessMemory>(); });
    }

    TEST("RandomAccessMemory_forwards_delegated_memory_reads")
    {
        ushort address = 0x42;
        byte value = 0x12;

        auto ram = std::make_shared<RandomAccessMemory>();

        auto addresses = std::vector<ushort> { address };
        auto delegateMock = CREATE_MOCK<DelegateMock>();
        delegateMock->SetDelegatedAddresses(addresses);
        delegateMock->byte_ReadByte_ushort_SetReturnValue(address, value);

        ram->RegisterDelegate(GET_OBJECT<MemoryAccessDelegate>(delegateMock));

        ASSERT_EQUAL<byte>(value, ram->ReadByte(address));
    }

    TEST("RandomAccessMemory_forwards_delegated_memory_writes")
    {
        ushort address = 0x42;
        byte value = 0x12;

        auto ram = std::make_shared<RandomAccessMemory>();

        auto addresses = std::vector<ushort> { address };
        auto delegateMock = CREATE_MOCK<DelegateMock>();
        delegateMock->SetDelegatedAddresses(addresses);

        ram->RegisterDelegate(GET_OBJECT<MemoryAccessDelegate>(delegateMock));

        value, ram->WriteByte(address, value);

        VERIFY_2P(delegateMock, WriteByte, ushort, address, byte, value, ONCE);
    }
}
TEST_FIXTURE_END