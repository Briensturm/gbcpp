#pragma once

#include <memory>
#include <array>

#include "gbcpp.hpp"
#include "ram_delegate.hpp"

class RandomAccessMemory
{
    public:
        RandomAccessMemory();

        mockable byte ReadByte(ushort address);
        void WriteByte(ushort address, byte data);

        void RegisterDelegate(RamDelegatePtr delegate);

    private:
        byte _interruptFlags = 0x01;
        byte _interruptEnable;

        //for CGB/DMG distinction        
        byte const _key1 = 0xFF;

        std::array<RamDelegatePtr, 0xFFFF+1> _ramDelegates;
        std::array<byte, 0xFFFF+1> _undelegatedMemory;
};

using RamPtr = std::shared_ptr<RandomAccessMemory>;