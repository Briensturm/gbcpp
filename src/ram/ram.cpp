#include "ram.hpp"

using namespace constants;

RandomAccessMemory::RandomAccessMemory()
{
    for(int i = 0; i<=0xFFFF; i++)
        _undelegatedMemory[i] = 0xFF;
}

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
    }          

    //check for a delegate
    auto delegate = _ramDelegates[address];
    if(delegate)
    {
        return delegate->ReadByte(address);
    }

    return _undelegatedMemory[address];
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
    }   

    //check for a delegate
    auto delegate = _ramDelegates[address];
    if(delegate)
    {
        delegate->WriteByte(address, data);
        return;
    }

    _undelegatedMemory[address] = data;
}

void RandomAccessMemory::RegisterDelegate(RamDelegatePtr delegate)
{
    auto addresses = delegate->GetDelegatedAddresses();

    for(ushort address : addresses) 
        _ramDelegates[address] = delegate;
}