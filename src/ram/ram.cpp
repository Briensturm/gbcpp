#include "ram.hpp"

using namespace constants;

byte RandomAccessMemory::ReadByte(ushort address)
{
    switch (address)
    {
        case reg::int_enable:
            return _interruptEnable;

        case reg::int_flags:
            return (byte)(0xE0 | _interruptFlags);

        //DMG/GBC distinction
        case 0xFF4D:
            return _key1;

        //insert cases for different components

    }            
    
    return 0xFF;
}
        
void RandomAccessMemory::WriteByte(ushort address, byte data)
{
    switch(address)
    {
        case reg::int_enable:
            _interruptEnable = data;
            break;

        case reg::int_flags:
            _interruptFlags = data;
            break;

        case 0xFF4D:
            break;

        //insert cases for different components
    }   
}