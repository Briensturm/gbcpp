#pragma once

#include "mock.hpp"
#include "ram/ram.hpp"

class RamMock : public RandomAccessMemory
{
    MOCK_METHOD_RET_P(byte, ReadByte, ushort);
};

