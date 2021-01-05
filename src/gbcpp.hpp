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
        const ushort int_enable = 0xFFFF;
        const ushort int_flags  = 0xFF0F;

        const ushort serial_data    = 0xFF01;
        const ushort serial_control = 0xFF02;

        const ushort joypad = 0xFF00;

        const ushort divider       = 0xFF04;
        const ushort timer         = 0xFF05;
        const ushort timer_load    = 0xFF06;
        const ushort timer_control = 0xFF07;
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