#pragma once

#include <vector>

#include "ppu_context.hpp"
#include "ram/ram.hpp"

class PixelProcessingUnit : MemoryAccessDelegate
{
    private:
        PPUCtxPtr _context;

    public:
        event EventHandler NextFrameReadyEvent
        {
            add { _context.NextFrameReadyEvent += value; }
            remove { _context.NextFrameReadyEvent -= value; }
        }

        PixelProcessingUnit(IRandomAccessMemory mainMemory)
        {
            _context = new PixelProcessingUnitContext(mainMemory);            
        }

        std::vector<ushort> GetDelegatedAddresses()
        {
            auto addressList = new List<ushort>();

            auto videoRegisterAddresses = new ushort[] { VideoRegisters.LcdControl,
                                                        VideoRegisters.LcdStatus,
                                                        VideoRegisters.LineY,
                                                        VideoRegisters.ScrollX,
                                                        VideoRegisters.ScrollY,
                                                        VideoRegisters.WindowX,
                                                        VideoRegisters.WindowY,
                                                        VideoRegisters.LineYCompare,
                                                        VideoRegisters.BackgroundPalette,
                                                        VideoRegisters.ObjectPalette0,
                                                        VideoRegisters.ObjectPalette1};

            auto vramAddresses = new ushort[0xA000 - 0x8000];
            for (int i = 0; i < vramAddresses.Length; i++)
                vramAddresses[i] = (ushort)(i + 0x8000);

            auto oamAddresses = new ushort[0xFEA0 - 0xFE00];
            for(int i = 0; i < oamAddresses.Length; i++)
                oamAddresses[i] = (ushort)(i + 0xFE00);

            addressList.AddRange(videoRegisterAddresses);
            addressList.AddRange(vramAddresses);
            addressList.AddRange(oamAddresses);

            return addressList.AsEnumerable();
        }

        byte DelegateMemoryRead(ushort address)
        {
            if (address >= 0x8000 && address <= 0x97FF)
                return _context.TileData[address - 0x8000];
            else if (address >= 0x9800 && address <= 0x9BFF)
                return _context.FirstTileMap[address - 0x9800];
            else if (address >= 0x9C00 && address <= 0x9FFF)
                return _context.SecondTileMap[address - 0x9C00];
            else if (address >= 0xFE00 && address <= 0xFE9F)
                return _context.SpriteTable.ReadSpriteAttributeTable(address);

            return address switch
            {
                VideoRegisters.LcdStatus => _context.LcdStatus,
                VideoRegisters.LcdControl => _context.LcdControl,
                VideoRegisters.LineY => (byte)_context.CurrentLine,//todo: force 0 when LCD is off
                VideoRegisters.LineYCompare => _context.LycRegister,
                VideoRegisters.ScrollX => _context.ScrollX,
                VideoRegisters.ScrollY => _context.ScrollY,
                VideoRegisters.WindowX => _context.WindowX,
                VideoRegisters.WindowY => _context.WindowY,
                VideoRegisters.BackgroundPalette => _context.BackgroundPalette,
                VideoRegisters.ObjectPalette0 => _context.ObjectPalette0,
                VideoRegisters.ObjectPalette1 => _context.ObjectPalette1,
                _ => throw new InvalidOperationException($"0x{address:X2} is not a valid ppu address"),
            };
        }

        void DelegateMemoryWrite(ushort address, byte data)
        {
            if (address >= 0x8000 && address <= 0x97FF)
            {
                //_logger.Log($"Writing tile data 0x{data:X2} at 0x{address:X2}");
                _context.TileData[address - 0x8000] = data;
            }
            else if (address >= 0x9800 && address <= 0x9BFF)
            {
                //_logger.Log($"Writing tile map 0 data 0x{data:X2} at 0x{address:X2}");
                _context.FirstTileMap[address - 0x9800] = data;
            }
            else if (address >= 0x9C00 && address <= 0x9FFF)
            {
                //_logger.Log($"Writing tile map 1 data 0x{data:X2} at 0x{address:X2}");
                _context.SecondTileMap[address - 0x9C00] = data;
            }
            else if(address >= 0xFE00 && address <= 0xFE9F)
            {
                _context.SpriteTable.WriteSpriteAttributeTable(address, data);
            }
            else
            {
                switch (address)
                {
                    case VideoRegisters.LcdControl:
                        _context.LcdControl = data;
                        break;
                    case VideoRegisters.LcdStatus:
                        _context.LcdStatus = data;                        
                        break;

                    case VideoRegisters.LineY:
                        //read only
                        break;

                    case VideoRegisters.LineYCompare:
                        _context.LycRegister = data;                       
                        break;

                    case VideoRegisters.ScrollX:
                        _context.ScrollX = data;
                        break;

                    case VideoRegisters.ScrollY:
                        _context.ScrollY = data;
                        break;

                    case VideoRegisters.WindowX:
                        _context.WindowX = data;
                        break;

                    case VideoRegisters.WindowY:
                        _context.WindowY = data;
                        break;

                    case VideoRegisters.BackgroundPalette:
                        _context.BackgroundPalette = data;
                        break;

                    case VideoRegisters.ObjectPalette0:
                        _context.ObjectPalette0 = data;
                        break;

                    case VideoRegisters.ObjectPalette1:
                        _context.ObjectPalette1 = data;
                        break;

                    default:
                        throw new InvalidOperationException($"0x{address:X2} is not a valid ppu address");
                }
            }
        }
    
        byte[] GetScreen()
        {
            return _context.ScreenBitmap;
        }
        
        void AdvanceMachineCycle()
        {
            if (_context.LcdEnable == 0)
                return;

            _context.AdvanceMachineCycle();
        }        
};
