#include "cpu_registers.hpp"

#include <stdexcept>

unsigned short CpuRegisters::ReadRegister(int index)
{
    switch(index)
    {
        case 0:
            return B;
            break;
        case 1:
            return C;  
            break;
        case 2:
            return D;
            break;
        case 3:
            return E;
            break;
        case 4:
            return H;
            break;
        case 5:
            return L;
            break;
        case 6:
            return HL;
            break;
        case 7:
            return A;
            break;
        default:
            throw std::out_of_range("Cpu does not have a register with index...");
    }
}

void CpuRegisters::WriteRegister(int index, unsigned short value)
{
    switch(index)
    {
        case 0:
            B = value;
            break;
        case 1:
            C = value;
            break;
        case 2:
            D = value;
            break;
        case 3:
            E = value;
            break;
        case 4:
            H = value;
            break;
        case 5:
            L = value;
            break;
        case 6:
            HL = value;
            break;
        case 7:
            A = value;
            break;
        default:
            throw std::out_of_range("Cpu does not have a register with index...");
    }
}

void CpuRegisters::Reset()
{
    A = 0x01;            

    BC = 0x0013;            
    DE = 0x00D8;
    HL = 0x014D;

    F = 0xB0;
}