#pragma once

#include <memory>
#include <vector>

#include "gbcpp.hpp"
#include "ram.hpp"

class MemoryAccessDelegate
{
    public:
        virtual byte ReadByte(ushort address) = 0;
        virtual void WriteByte(ushort address, byte data) = 0;

        virtual std::vector<ushort> GetDelegatedAddresses() const = 0;
};

using RamDelegatePtr = std::shared_ptr<MemoryAccessDelegate>;