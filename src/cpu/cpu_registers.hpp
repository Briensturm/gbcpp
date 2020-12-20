#pragma once

#include <memory>

#include "reg_16bit.hpp"

struct CpuRegisters
{
    public:
        unsigned short ReadRegister(int index);
        void WriteRegister(int index, unsigned short value);

        void Reset();       

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

        FlagRegister F = FlagRegister(HalfCarryFlag, CarryFlag, ZeroFlag, SubtractionFlag);

        bool HalfCarryFlag;
        bool CarryFlag;
        bool ZeroFlag;
        bool SubtractionFlag;

    private:
        uint8_t _a, _b, _c, _d, _e, _h, _l;
};

using RegistersPtr = std::shared_ptr<CpuRegisters>;