//
// Created by dell on 2019/4/17.
//

#include <algorithm>
#include "../include/MMU.h"
#include "../include/Exceptions.h"

AddressSpace& MMU::findAddressSpace(Word address) const{
    for (AddressSpace& s: spaces){
        if (s.accepts(address))
            return s;
    }
    throw;
}

Byte MMU::readByte(Word address) const {
    auto& s = findAddressSpace(address);
    return s.getByte(address);
}

Word MMU::readWord(Word address) const {
    return readByte(address) | readByte((Word)(address + 1)) << 8;
}

void MMU::writeByte(Word address, Byte value) const {
    auto& s = findAddressSpace(address);
    s.setByte(address, value);
}

void MMU::writeWord(Word address, Word value) const {
    writeByte(address, (value & 0xFF));
    writeByte(address + 1, (value >> 8));
}

void MMU::addAddressSpace(AddressSpace& s) {
    spaces.emplace_back(s);
}

void MMU::removeAddressSpace(AddressSpace& s) {
    spaces.erase(std::remove_if(spaces.begin(), spaces.end(), [&s](auto& t){
        return &s == &(t.get());
    }), spaces.end());
}

void MMU::init() {
}

MMU *MMU::getMMU() {
    static MMU mmu;
    return &mmu;
}
