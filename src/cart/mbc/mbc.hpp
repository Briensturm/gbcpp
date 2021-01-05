#pragma once

#include <stdexcept>
#include <vector>
#include <memory>

#include "cart/cart.hpp"
#include "cart/ram_loader.hpp"
#include "cart/rom_loader.hpp"
#include "ram/ram.hpp"

class MBC : MemoryAccessDelegate
{
    public:
        MBC(std::vector<byte> romData)
        {
            _romData = romData;

            //check if CGB-only game (not supported for now)
            if (_romData[0x0143] == 0xC0)
                throw std::logic_error("CGB-only games are not supported");
            
            _cartridgeType = (CartridgeType)romData[0x0147];

            _romSizeType = (RomSizeType)_romData[0x0148];
            _ramSizeType = (RamSizeType)_romData[0x0149];

            _ramData = std::vector<byte>();
            _ramData.resize(RamSizeInBytes());            
        }

        void LoadRam(RamLoaderPtr ramLoader)
        {
            if (!CartridgeCanSave())
                return;

            auto data = ramLoader->TryLoadRam();

            if (data.size() > 0)
                _ramData = data;
        }

        void SaveRam(RamLoaderPtr ramLoader)
        {
            if (CartridgeCanSave())
                ramLoader->SaveRam(_ramData);
        }

        virtual byte ReadByte(ushort address) = 0;
        virtual void WriteByte(ushort address, byte data) = 0;        

        std::vector<ushort> GetDelegatedAddresses() const
        {
            auto addresses = std::vector<ushort>();
            addresses.reserve(0xA000);

            //add rom addresses
            for(ushort i = 0x0; i<0x8000; i++)
                addresses.push_back(i);
            
            //add ram addresses
            for(ushort i = 0xA000; i<0xC000; i++)
                addresses.push_back(i);

            return addresses;
        }

    protected:
        virtual bool CartridgeCanSave() const = 0;

        int RamSizeInBytes()
        {
            switch(_ramSizeType)
            {
                case RamSizeType::Ram_2KB:
                    return 0x800;
                case RamSizeType::Ram_8KB:
                    return 0x2000;
                case RamSizeType::Ram_32KB: 
                    return 0x8000;
                case RamSizeType::Ram_64KB: 
                    return 0x10000;
                case RamSizeType::Ram_128KB: 
                    return 0x20000;
                case RamSizeType::None:
                    return 0;
                
                default:
                    return 0;
            }           
        }

        std::vector<byte> _romData;
        std::vector<byte> _ramData;        

        RomSizeType _romSizeType;
        RamSizeType _ramSizeType;

        CartridgeType _cartridgeType;
};

using MBCPtr = std::shared_ptr<MBC>;