#pragma once

#include "mock.hpp"

#include "ram/ram.hpp"

using ushortv = std::vector<ushort>;

class DelegateMock : public MemoryAccessDelegate
{
    MOCK_METHOD_2P(WriteByte, ushort, byte);
    MOCK_METHOD_RET_P(byte, ReadByte, ushort);    

    std::vector<ushort> GetDelegatedAddresses() const
    {
        return _addresses;
    }    

    void SetDelegatedAddresses(std::vector<ushort> addresses)
    {
        _addresses = addresses;
    }

    std::vector<ushort> _addresses;
};