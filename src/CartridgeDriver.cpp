//
// Created by dell on 2019/6/3.
//

#include "../include/CartridgeDriver.h"
#include "../include/Cartridges/Cartridge_ROM0.h"
#include "../include/Cartridges/Cartridge_MBC1.h"
#include "../include/Exceptions.h"


void CartridgeDriver::openFile(const std::string &filePath) {
    this->filePath = filePath;
    std::ifstream romStream;
    try {
        romStream.open(filePath, std::ios::binary);
        if (!romStream) {
            throw FileNotFoundException("driver[open file]", filePath);
        }
    } catch (...) {
        throw;
    }
#ifndef NLOG
    logger << "game loaded:" << getTitle() << std::endl;
#endif
    char header[0x150] = {0};
    romStream.read(header, 0x150);
    romStream.close();
    cartridgeType = (Byte) header[0x147];
    romBankCode = (Byte) header[0x148];
    if (romBankCode < 0x10) {
        romSize = (32_kByte) << romBankCode;
    } else {
        romSize = romSizeMap[romBankCode - 0x52] * 16_kByte;
    }

    ramBankCode = (Byte) header[0x149];
    ramSize = ramSizeMap[ramBankCode] * 1024;
    title.reserve(0x142 - 0x134);
    std::copy(header + 0x134, header + 0x142, title.begin());

    loadCartridge();
}

void CartridgeDriver::loadCartridge() {
    switch (cartridgeType) {
        case 0:
            cartridge = std::make_unique<Cartridge_ROM0>(filePath);
            break;
        case 1:
        case 2:
        case 3:
            cartridge = std::make_unique<Cartridge_MBC1>(filePath, romSize, ramSize);
            break;
    }
}

CartridgeDriver::~CartridgeDriver() {

}


const std::string& CartridgeDriver::getTitle() const {
    return title;
}

bool inline CartridgeDriver::accepts(Word address) const {
    return cartridge->accepts(address);
}

Byte inline CartridgeDriver::getByte(Word address) const {
    return cartridge->getByte(address);
}

void inline CartridgeDriver::setByte(Word address, Byte value) {
    cartridge->setByte(address, value);
}