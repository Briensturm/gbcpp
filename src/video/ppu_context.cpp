#include "ppu_context.hpp"

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

void PixelProcessingUnitContext::SetLcdEnable(int value)
{
    LcdEnable = value;

    if (value == 0)
    {
        CurrentLine = 0;
        _stateMachine.TransitionTo<OamScanState>();

        for (int i = 0; i < ScreenBitmap.Length / 3; i++)
        {
            WriteToScreenBitmap(175, i * 3);
            WriteToScreenBitmap(203, i * 3 +1);
            WriteToScreenBitmap(70, i * 3 +2);
        }

        SwapBuffers();
        NotifyNextFrameReady();                
    }
}

internal byte LcdStatus
{
    get
    {
        return (byte)(0x80 |
                    (_coincidenceInterrupt << 6) |
                    (_oamInterrupt << 5) |
                    (_vblankInterrupt << 4) |
                    (_hblankInterrupt << 3) |
                    (CheckLyCoincidence() << 2) |
                    _stateMachine.GetModeNumber());
    }

    set
    {
        _coincidenceInterrupt = (value >> 6) & 0x01;
        _oamInterrupt = (value >> 5) & 0x01;
        _vblankInterrupt = (value >> 4) & 0x01;
        _hblankInterrupt = (value >> 3) & 0x01;

        if (ShouldStatIrqBeRaised())
            RaiseStatInterrupt();
    }
}

internal byte LcdControl
{
    get
    {
        return (byte)(LcdEnable << 7 |
                    (WindowTileMap << 6) |
                    (WindowEnable << 5) |
                    (_bgWindowTileData << 4) |
                    (BackgroundTileMap << 3) |
                    (SpriteSize << 2) |
                    (SpriteEnable << 1) |
                    (BackgroundEnable << 0));
    }
    set
    {
        SetLcdEnable((value >> 7) & 0x01);
        WindowTileMap = (value >> 6) & 0x01;
        WindowEnable = (value >> 5) & 0x01;
        _bgWindowTileData = (value >> 4) & 0x01;
        BackgroundTileMap = (value >> 3) & 0x01;
        SpriteSize = (value >> 2) & 0x01;
        SpriteEnable = (value >> 1) & 0x01;
        BackgroundEnable = (value >> 0) & 0x01;
    }
}

PixelProcessingUnitContext::PixelProcessingUnitContext(RamPtr mainMemory)
{
    _mainMemory = mainMemory;

    _stateMachine = new PPUStateMachine(this);

    SpriteTable = new SpriteTable();
    _spritesToBeDrawn = new List<Sprite>();

    FirstTileMap = new byte[32 * 32];
    SecondTileMap = new byte[32 * 32];
    TileData = new byte[6144];

    _screenBuffer0 = new byte[Common.Constants.Video.ScreenWidth * Common.Constants.Video.ScreenHeight * 3];
    _screenBuffer1 = new byte[Common.Constants.Video.ScreenWidth * Common.Constants.Video.ScreenHeight * 3];

    LcdControl = 0x91;
}

int PixelProcessingUnitContext::CheckLyCoincidence()
{
    return CurrentLine == LycRegister ? 1 : 0;
}

void PixelProcessingUnitContext::NotifyNextFrameReady()
{
    NextFrameReadyEvent?.Invoke(this, null);
}

void PixelProcessingUnitContext::RequestVBlankInterrupt()
{
    auto currentIf = _mainMemory.ReadByte(MiscRegisters.InterruptFlags);
    _mainMemory.WriteByte(MiscRegisters.InterruptFlags, (byte)(currentIf | 0x01));

    NotifyNextFrameReady();

    SwapBuffers();
}

int PixelProcessingUnitContext::GetCurrentLine()
{
    if (LcdEnable == 1)
        return _currentLine;
    else
        return 0;
}   

int PixelProcessingUnitContext::SetCurrentLine()
{
    _currentLine = value;
}

void PixelProcessingUnitContext::AdvanceMachineCycle()
{
    _stateMachine.AdvanceMachineCycle();

    if (ShouldStatIrqBeRaised())
        RaiseStatInterrupt();
}

bool PixelProcessingUnitContext::GetStatSignal()
{
    if (LcdEnable == 0)
        return false;

    return ((CheckLyCoincidence() & _coincidenceInterrupt) == 0x01) ||
        (_stateMachine.GetModeNumber() == 0 && _hblankInterrupt == 1) ||
        (_stateMachine.GetModeNumber() == 2 && _oamInterrupt == 1) ||
        (_stateMachine.GetModeNumber() == 1 && (_vblankInterrupt == 1 || _oamInterrupt == 1));
}

bool PixelProcessingUnitContext::ShouldStatIrqBeRaised()
{
    //check for stat interrupt
    auto newStatSignal = GetStatSignal();

    //detect rising edge
    auto raiseStatIrq = newStatSignal && !_statSignal;
    _statSignal = newStatSignal;

    return raiseStatIrq;
}

void PixelProcessingUnitContext::RaiseStatInterrupt()
{
    auto currentIf = _mainMemory.ReadByte(MiscRegisters.InterruptFlags);
    _mainMemory.WriteByte(MiscRegisters.InterruptFlags, (byte)(currentIf | 0x02));
}

void PixelProcessingUnitContext::SwapBuffers()
{
    _buffersSwapped = !_buffersSwapped;
}
