#pragma once

#include <stdexcept>

#include "Reg16Bit.hpp"

struct CpuRegisters
{
    public:
        Reg8Bit A = Reg8Bit(_a);
        Reg8Bit B = Reg8Bit(_b);
        Reg8Bit C = Reg8Bit(_c);
        Reg8Bit D = Reg8Bit(_d);
        Reg8Bit E = Reg8Bit(_e);
        Reg8Bit H = Reg8Bit(_h);
        Reg8Bit L = Reg8Bit(_l);     

        Reg16Bit BC = Reg16Bit(_b, _c);
        Reg16Bit DE = Reg16Bit(_d, _e);
        Reg16Bit HL = Reg16Bit(_h, _l);

        bool HalfCarryFlag;
        bool CarryFlag;
        bool ZeroFlag;
        bool SubtractionFlag;


    /*int8_t F
    {
        get
        {
            return (int8_t)(((ZeroFlag ? 1 : 0) << 7) |
                            ((SubtractionFlag ? 1 : 0) << 6) |
                            ((HalfCarryFlag ? 1 : 0) << 5) |
                            ((CarryFlag ? 1 : 0) << 4));
        }

        set
        {
            ZeroFlag = (value & 0x80) == 0x80;
            SubtractionFlag = (value & 0x40) == 0x40;
            HalfCarryFlag = (value & 0x20) == 0x20;
            CarryFlag = (value & 0x10) == 0x10;
        }
    }*/ 

    unsigned short ReadRegister(int index)
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

    void WriteRegister(int index, unsigned short value)
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

    void Reset()
    {
        A = 0x01;            
        B = 0x00;
        C = 0x13;
        D = 0x00;
        E = 0xD8;
        H = 0x01;
        L = 0x4D;

        HalfCarryFlag = true;
        CarryFlag = true;
        ZeroFlag = true;
        SubtractionFlag = false;
    }

    private:
        int8_t _a, _b, _c, _d, _e, _h, _l;
};