#pragma once

#include <memory>

#include "gbcpp.hpp"

class RandomAccessMemory
{
    public:
        mockable byte ReadByte(ushort address);
        void WriteByte(ushort address, byte data);        

    private:
        byte _interruptFlags = 0x01;
        byte _interruptEnable;

        //for CGB/DMG distinction        
        byte const _key1 = 0xFF;
};

using RamPtr = std::shared_ptr<RandomAccessMemory>;