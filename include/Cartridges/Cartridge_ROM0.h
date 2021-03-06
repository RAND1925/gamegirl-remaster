//
// Created by dell on 2019/6/15.
//

#ifndef GAMEGIRL_CARTRIDGE_ROM0_H
#define GAMEGIRL_CARTRIDGE_ROM0_H

#include "Cartridge.h"
#include <array>
#include <fstream>

class Cartridge_ROM0: public Cartridge{
private:
    std::array<Byte, 0x8000> rom{};
    std::string filePath;
public:
    bool accepts(Word address) const override;
    Byte getByte(Word address) const override;
    void setByte(Word address, Byte value) override;
    explicit Cartridge_ROM0(const std::string & filePath);
};



#endif //GAMEGIRL_CARTRIDGE_ROM0_H
