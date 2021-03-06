// cpu
// Created by dell on 2019/4/16.
//

#ifndef GAMEGIRL_CPU_H
#define GAMEGIRL_CPU_H

#include <functional>
#include "common.h"

class CPU {

public:
    Byte step();
    inline Word getPC(){return registers.pc;};
    void initRegisters();
    void initRegistersAfterBoot();
    void initMap();
    static CPU* getCPU();

protected:
    CPU()= default;

private:
    struct Registers {
        Byte a, f, b, c, d, e, h, l;
        Word sp, pc;
    } registers{}, backup{};

    using FlagSetter = std::function<void(void)>;
    using FlagGetter = std::function<Byte(void)>;
    using AllFlagSetter = std::function<void(Byte, Byte, Byte, Byte)>;
    FlagSetter setZ = [this]() { setBit<7>(registers.f); };
    FlagSetter setN = [this]() { setBit<6>(registers.f); };
    FlagSetter setH = [this]() { setBit<5>(registers.f); };
    FlagSetter setC = [this]() { setBit<4>(registers.f); };
    FlagSetter resetZ = [this]() { resetBit<7>(registers.f); };
    FlagSetter resetN = [this]() { resetBit<6>(registers.f); };
    FlagSetter resetH = [this]() { resetBit<5>(registers.f); };
    FlagSetter resetC = [this]() { resetBit<4>(registers.f); };
    FlagGetter getZ = [this]() -> Byte { return getBit<7>(registers.f); };
    FlagGetter getN = [this]() -> Byte { return getBit<6>(registers.f); };
    FlagGetter getH = [this]() -> Byte { return getBit<5>(registers.f); };
    FlagGetter getC = [this]() -> Byte { return getBit<4>(registers.f); };
    AllFlagSetter setZNHC = [this](Byte z, Byte n, Byte h, Byte c) {
        registers.f = (z << 7u) | (n <<  6u) | (h << 5u) | (c << 4u);
    };
    //tool functions to run opcodes
    inline Byte getImmediateValue8();
    inline Word getImmediateValue16();
    inline SByte getSignedImmediateValue8();
    inline void ld8(Byte &lhs, Byte rhs);
    inline void ld16(Word &lhs, Word rhs);
    inline Word getR16(Byte high, Byte low);
    inline void setR16(Byte &high, Byte &low, Word t);
    inline Word getAF();
    inline Word getHL();;
    inline Word getBC();;
    inline Word getDE();;
    inline void setAF(Word t);;
    inline void setHL(Word t);;
    inline void setBC(Word t);;
    inline void setDE(Word t);;
    inline void push16(Word val);
    inline Word pop16();
    inline Byte add(Byte a, Byte b);
    inline Byte adc(Byte a, Byte b);
    inline Word add(Word a, Word b);
    inline Word addSp(Word a, SByte b);
    inline Byte sub(Byte a, Byte b);
    inline Byte sbc(Byte a, Byte b);
    inline Byte andAL(Byte a, Byte b);
    inline Byte orAL(Byte a, Byte b);
    inline Byte xorAL(Byte a, Byte b);
    inline void cp(Byte a, Byte b);
    inline Byte inc(Byte a);
    inline Word inc(Word a);
    inline Byte dec(Byte a);
    inline Word dec(Word a);
    inline Byte swap(Byte a);
    inline void daa();
    inline Byte cpl(Byte a);
    inline void ccf();
    inline void scf();
    inline Byte rlc(Byte a);
    inline Byte rl(Byte a);
    inline Byte rrc(Byte a);
    inline Byte rr(Byte a);
    inline Byte sla(Byte a);
    inline Byte sra(Byte a);
    inline Byte srl(Byte a);
    inline void bit(Byte b, Byte a);
    inline Byte set(Byte b, Byte a);
    inline Byte res(Byte b, Byte a);
    inline void jump(Word addr);
    inline void jr(Byte r);
    inline void call(Word addr);
    inline void ret();
    inline void rsv();
    inline void rls();
    inline void restart(Word addr);

    std::function<Byte(void)> opMap[0x100];
    std::function<Byte(void)> opCBMap[0x100];

#ifndef NLOG
private:
    void display();
#endif
};

extern CPU cpu;

#endif //GAMEGIRL_CPU_H
