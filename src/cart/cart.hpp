#pragma once
    
enum class CartridgeType
{
    ROM_ONLY                = 0x00,
    MBC1                    = 0x01,
    MBC1_RAM                = 0x02,
    MBC1_RAM_BATTERY        = 0x03,
    MBC2                    = 0x05,
    MBC2_BATTERY            = 0x06,
    ROM_RAM                 = 0x08,
    ROM_RAM_BATTERY         = 0x09,
    MBC3_TIMER_BATTERY      = 0x0F,
    MBC3_TIMER_RAM_BATTERY  = 0x10,
    MBC3                    = 0x11,
    MBC3_RAM                = 0x12,
    MBC3_RAM_BATTERY        = 0x13,
    MBC5                    = 0x19,
    MBC5_RAM                = 0x1A,
    MBC5_RAM_BATTERY        = 0x1B,
    MBC5_RUMBLE             = 0x1C,
    MBC5_RUMBLE_RAM         = 0x1D,
    MBC5_RUMBLE_RAM_BATTERY = 0x1E,
};

enum class RomSizeType
{
    Rom_32KB  = 0x00,
    Rom_64KB  = 0x01,
    Rom_128KB = 0x02,
    Rom_256KB = 0x03,
    Rom_512KB = 0x04,
    Rom_1MB   = 0x05,
    Rom_2MB   = 0x06,
    Rom_4MB   = 0x07,
    Rom_8MB   = 0x08,
};

enum class RamSizeType
{
    None = 0x00,

    Ram_2KB   = 0x01,
    Ram_8KB   = 0x02,
    Ram_32KB  = 0x03,
    Ram_128KB = 0x04,
    Ram_64KB  = 0x05,
};
