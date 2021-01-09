#pragma once

#include <memory>

#include "gbcpp.hpp"

#include "ram/ram.hpp"

class PixelProcessingUnitContext
{
    SpriteTable SpriteTable;
    List<Sprite> _spritesToBeDrawn;

    //when setting lycreg:
    // if (ShouldStatIrqBeRaised())
    //                  RaiseStatInterrupt();
    byte LycRegister;

    byte[] ScreenBitmap
    {
        get 
        {
            if (_buffersSwapped)
                return _screenBuffer1;

            return _screenBuffer0;
        }
    }

    void WriteToScreenBitmap(byte data, int index)
    {
        if (_buffersSwapped)
            _screenBuffer0[index] = data;
        else
            _screenBuffer1[index] = data;
    }        

    public:
        PixelProcessingUnitContext(RamPtr mainMemory);

        void RequestVBlankInterrupt();
        int GetCurrentLine();      
        void AdvanceMachineCycle();

        void SetLcdStatus(byte value);
        byte GetLcdStatus();
        void SetLcdControl(byte value);
        byte GetLcdControl();

        int WindowTileMap;
        int WindowEnable;
        int _bgWindowTileData;
        int BackgroundTileMap;
        int SpriteSize;
        int SpriteEnable;
        int BackgroundEnable;

        byte BackgroundPalette = 0xFC;

        byte ScrollX;
        byte ScrollY;
        byte WindowX;
        byte WindowY;

        byte ObjectPalette0;
        byte ObjectPalette1;

        byte TileData[];
        byte FirstTileMap[];
        byte SecondTileMap[];

        int LcdEnable;

        event NextFrameReadyEvent;

    private:
        int CheckLyCoincidence();
        void NotifyNextFrameReady();
        bool GetStatSignal();
        bool ShouldStatIrqBeRaised();
        void RaiseStatInterrupt();
        void SwapBuffers();

        void SetLcdEnable(int value);

        RamPtr _mainMemory;

        int _currentLine;

        int _coincidenceInterrupt;
        int _oamInterrupt;
        int _vblankInterrupt;
        int _hblankInterrupt;

        bool _statSignal;

        bool _buffersSwapped = false;

        byte _screenBuffer0[];
        byte _screenBuffer1[];

        PPUSmPtr _stateMachine;
};

using PPUCtxPtr = std::shared_ptr<PixelProcessingUnitContext>;
