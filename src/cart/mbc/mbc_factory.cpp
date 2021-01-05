#include "mbc_factory.hpp"

#include <stdexcept>
#include <memory>

#include "cart.hpp"
#include "mbc0.hpp"

MBCPtr MBCFactory::CreateMBC(RomLoaderPtr romLoader) const
{
    auto romData = romLoader->LoadRom();
    auto cartridgeType = (CartridgeType)romData[0x0147];

    switch (cartridgeType)
    {
        case CartridgeType::ROM_ONLY:
        case CartridgeType::ROM_RAM:
        case CartridgeType::ROM_RAM_BATTERY:
            return std::make_shared<MBC0>(romData);

        default:
            throw std::logic_error("Cartridge type is not supported");
    }
}
