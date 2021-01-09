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

        const ushort lcd_control = 0xFF40;
        const ushort lcd_status  = 0xFF41;

        const ushort scroll_y      = 0xFF42;
        const ushort scroll_x      = 0xFF43;
        const ushort line_y        = 0xFF44;
        const ushort liney_compare = 0xFF45;
        const ushort window_y      = 0xFF4A;
        const ushort window_x      = 0xFF4B;

        const ushort dma_transfer = 0xFF46;

        const ushort bg_palette  = 0xFF47;
        const ushort obj_palette0 = 0xFF48;
        const ushort obj_palette1 = 0xFF49;  
    }

    namespace int_addr
    {
        const ushort vblank = 0x0040;
        const ushort lcd    = 0x0048;
        const ushort timer  = 0x0050;
        const ushort serial = 0x0058;
        const ushort joypad = 0x0060;
    }

    namespace cart
    {
        const ushort fbank_addrend = 0x3FFF;
        const ushort rom_addrend   = 0x7FFF;
        const ushort cram_addrbeg  = 0xA000;
        const ushort cram_addrend  = 0xBFFF;

        const ushort rombank_size = 0x4000;
        const ushort rambank_size = 0x2000;
    }

    namespace vid
    {
        const int screen_w = 160;
        const int screen_h = 144;

        const int line_count = 154;
        const int dots_line = 456;

        const int hblank_mode = 0;
        const int vblank_mode = 1;
        const int oamscan_mode = 2;
        const int pixelwriting_mode = 3;

        enum class shades
        {
            white = 0x00,
            lgrey = 0x01,
            mgrey = 0x10,
            black = 0x11,
        };
    }
}