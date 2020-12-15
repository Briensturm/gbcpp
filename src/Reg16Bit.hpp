#pragma once

#include <stdint.h>

class Reg16Bit
{
    public:
        Reg16Bit(int8_t &highNibble, int8_t &lowNibble) 
            : _highNibble(highNibble), _lowNibble(lowNibble) {}

        virtual void operator = (const unsigned short &value) 
        { 
            _highNibble = value >> 8;
            _lowNibble = (uint8_t)value;
        }
        virtual operator unsigned short () const 
        { 
            return (unsigned short)(_highNibble << 8 | _lowNibble); 
        }       

    protected:
        int8_t &_highNibble;
        int8_t &_lowNibble;
};

class Reg8Bit : public Reg16Bit
{
    public:
        Reg8Bit(int8_t &lowNibble) : Reg16Bit(dummy, lowNibble) {}

        void operator = (const unsigned short &value) 
        { 
            _lowNibble = (uint8_t)value;
        }
        operator unsigned short () const  
        { 
            return _lowNibble;
        }     

    private:
        int8_t dummy;
};