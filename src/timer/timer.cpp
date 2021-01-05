#include "timer.hpp"

#include <stdexcept>

#include "gbcpp.hpp"

using namespace constants;

std::vector<ushort> Timer::GetDelegatedAddresses() const
{
    std::vector<ushort> addresses = { reg::divider,
                                      reg::timer_control,
                                      reg::timer_load,
                                      reg::timer };

    return addresses;
}

byte Timer::DelegateMemoryRead(ushort address)
{
    switch(address)
    {
        case reg::divider:
            return (byte)(_div >> 8);

        case reg::timer:
            return _tima;

        case reg::timer_load:
            return _tma;

        case reg::timer_control:
            return (byte)(_tac | 0xF8);

        default:
            throw std::logic_error("invalid timer address");
    }
}

void Timer::DelegateMemoryWrite(ushort address, byte data)
{
    switch (address)
    {
        case reg::divider:
        {
            auto oldDiv = _div;
            _div = 0;

            if (TimerIsEnabled() && DivFallingEdgeOccured(oldDiv, 0))
                IncrementTima();
            break;
        }

        case reg::timer:
        {
            if (_loadTimaFromTmaCycle)
                return;

            _tima = data;
            _waitCycle = false;
            break;
        }

        case reg::timer_load:
        {
            _tma = data;
            break;
        }

        case reg::timer_control:
        {
            auto oldMuxOut = TimerIsEnabled() && ((_div >> _controlBits[_tac & 0x03]) & 0x01) == 0x01;
            _tac = data;

            auto newMuxOut = TimerIsEnabled() && ((_div >> _controlBits[_tac & 0x03]) & 0x01) == 0x01;

            //detect falling edge
            if (oldMuxOut && !newMuxOut)
                IncrementTima();
            break;
        }

        default:
            throw std::logic_error("invalid timer address");
    }
}

void Timer::AdvanceMachineCycle()
{
    //increase div with system clock
    auto oldDiv = _div;
    _div += 4;

    if(_waitCycle)
    {
        _waitCycle = false;
        _loadTimaFromTmaCycle = true;
    }
    else if(_loadTimaFromTmaCycle)
    {
        _loadTimaFromTmaCycle = false;
        _tima = _tma;

        //TODO: implement writing with bitmask
        auto currentIf = _mainMemory->ReadByte(reg::int_flags);
        _mainMemory->WriteByte(reg::int_flags, (byte)(currentIf | 0x04));
    }
    else if (!TimerIsEnabled())
        return;            

    if (DivFallingEdgeOccured(oldDiv, _div))
    {
        IncrementTima();
    }
}

void Timer::IncrementTima()
{ 
    _tima++;

    if (_tima == 0)
        _waitCycle = true;
}

bool Timer::DivFallingEdgeOccured(ushort divBefore, ushort divAfter)
{
    auto bit = _controlBits[_tac & 0x03];

    auto bitValueBefore = (divBefore >> bit) & 0x01;
    auto bitValueAfter = (divAfter >> bit) & 0x01;

    return bitValueBefore == 1 && bitValueAfter == 0;
}

bool Timer::TimerIsEnabled()
{
    return (_tac & 0x04) == 0x04; 
}
