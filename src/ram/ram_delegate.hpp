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

        void AssignRam(RamPtr ram);

    private:
        RamPtr _ram;
};

using RamDelegatePtr = std::shared_ptr<MemoryAccessDelegate>;