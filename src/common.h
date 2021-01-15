// generic tools
// Created by dell on 2019/4/17.
//

#ifndef GAMEGIRL_COMMON_H
#define GAMEGIRL_COMMON_H
#include <cstdint>

    using Byte = std::uint8_t;
    using Word = std::uint16_t;
    using SByte = std::int8_t;
    inline constexpr unsigned long long operator "" _kByte(const unsigned long long w){
        return w << 10;
    }

    template<int p, int f = 1<<p >
    constexpr Byte getBit(Byte b) {
        return (b >> p) & 1;
    }

    template<int p, int f = 1<<p >
    constexpr void setBit(Byte &b) {
        b |= f;
    }

    template<int p, int f = ~(1<<p) >
    constexpr void resetBit(Byte &b) {
        b &= f;
    }
    
    constexpr Byte getBit(Byte b, Byte p) {
        return static_cast<Byte>(b >> p) & 1;
    }
    constexpr void setBit(Byte &b, const Byte p) {
        b |= (1 << p);
    }
    constexpr  void resetBit(Byte &b, const Byte p){
        b &= ~(1 << p);
    }
#endif //GAMEGIRL_COMMON_H
