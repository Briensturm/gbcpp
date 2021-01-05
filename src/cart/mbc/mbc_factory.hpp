#pragma once

#include "mbc.hpp"
#include "rom_loader.hpp"

class MBCFactory
{
    public:
        MBCPtr CreateMBC(RomLoaderPtr romLoader) const;
};
