#pragma once

#include <vector>
#include <stdexcept>

#include "gbcpp.hpp"
#include "mbc.hpp"

using namespace constants;

class MBC0 : public MBC
{
    public:
        MBC0(std::vector<byte> romData) : MBC(romData) {}

        byte ReadByte(ushort address)
        {
            if (address <= cart::rom_addrend)
                return _romData[address];

            else if (address >= cart::cram_addrbeg && address <= cart::cram_addrend)
                return _ramData[cart::cram_addrbeg - address];

            else
                throw std::logic_error("Memory read at out of bounds address");
        }

        void WriteByte(ushort address, byte data)
        {
            if (address >= cart::cram_addrbeg && address <= cart::cram_addrend)
                _ramData[cart::cram_addrbeg - address] = data;
        }        

        bool CartridgeCanSave() const
        {
            return _cartridgeType == CartridgeType::ROM_RAM_BATTERY;
        } 
};
