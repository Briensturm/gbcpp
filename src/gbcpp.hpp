#pragma once

#include <stdint.h>

using ushort = unsigned short;
using byte = uint8_t;
using sbyte = int8_t;

#define mockable virtual

namespace constants
{
    namespace reg
    {
        ushort const int_enable = 0xFFFF;
        ushort const int_flags = 0xFF0F;

        ushort const serial_data = 0xFF01;
        ushort const serial_control = 0xFF02;

        ushort const joypad = 0xFF00;
    }

    namespace int_addr
    {
        const ushort vblank = 0x0040;
        const ushort lcd    = 0x0048;
        const ushort timer  = 0x0050;
        const ushort serial = 0x0058;
        const ushort joypad = 0x0060;
    }
}