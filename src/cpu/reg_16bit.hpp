#pragma once

#include <stdint.h>

#include "types.hpp"

class Reg16Bit
{
    public:
        Reg16Bit(byte &highNibble, byte &lowNibble) 
            : _highNibble(highNibble), _lowNibble(lowNibble) {}

        virtual void operator = (const ushort &value) 
        { 
            _highNibble = value >> 8;
            _lowNibble = (byte)value;
        }
        virtual operator ushort () const 
        { 
            return (ushort)(_highNibble << 8 | _lowNibble); 
        }       

    protected:
        byte &_highNibble;
        byte &_lowNibble;
};

class Reg8Bit : public Reg16Bit
{
    public:
        Reg8Bit(byte &lowNibble) : Reg16Bit(dummy, lowNibble) {}

        void operator = (const ushort &value) 
        { 
            _lowNibble = (byte)value;
        }
        operator ushort () const  
        { 
            return _lowNibble;
        }     

    private:
        byte dummy;
};

class FlagRegister
{
    public:
        FlagRegister(bool &halfCarryFlag, bool &carryFlag, bool &zeroFlag, bool &subFlag) 
            : _HalfCarryFlag(halfCarryFlag), _CarryFlag(carryFlag),
              _ZeroFlag(zeroFlag), _SubtractionFlag(subFlag) {}

        virtual void operator = (const byte &value) 
        { 
            _ZeroFlag = (value & 0x80) == 0x80;
            _SubtractionFlag = (value & 0x40) == 0x40;
            _HalfCarryFlag = (value & 0x20) == 0x20;
            _CarryFlag = (value & 0x10) == 0x10;
        }
        virtual operator byte () const 
        { 
            return static_cast<byte>((_ZeroFlag << 7) |
                                    (_SubtractionFlag << 6) |
                                    (_HalfCarryFlag << 5) |
                                    (_CarryFlag << 4));
        }       

    private:
        bool &_HalfCarryFlag;
        bool &_CarryFlag;
        bool &_ZeroFlag;
        bool &_SubtractionFlag;
};