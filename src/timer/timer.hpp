#pragma once

#include <vector>

#include "ram/ram.hpp"
#include "ram/ram_delegate.hpp"

class Timer : public MemoryAccessDelegate
{
    public:
    Timer(RamPtr mainMemory) : _mainMemory(mainMemory) {};

    std::vector<ushort> GetDelegatedAddresses() const;

    byte DelegateMemoryRead(ushort address);
    void DelegateMemoryWrite(ushort address, byte data); 

    void AdvanceMachineCycle();

    private:
        void IncrementTima();    
        bool DivFallingEdgeOccured(ushort divBefore, ushort divAfter);
        bool TimerIsEnabled();

        ushort _div = 0xABD0-4;
        byte _tma;
        byte _tima;
        byte _tac;

        int _controlBits[4] = { 9, 3, 5, 7 };

        const RamPtr _mainMemory;

        bool _loadTimaFromTmaCycle;
        bool _waitCycle;    
};
