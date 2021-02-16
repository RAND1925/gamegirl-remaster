//
// Created by dell on 2019/6/15.
//

#include "../include/EmptySpace.h"

bool EmptySpace::accepts(Word address) const {
    return address >= 0xFEA0 && address <= 0xFF80;
}

Byte EmptySpace::getByte(Word address) const {
    return bytes[address - 0xFFA0];
}

void EmptySpace::setByte(Word address, Byte value) {
    bytes[address - 0xFEA0] = value;
}

EmptySpace *EmptySpace::getEmptySpace() {
    static EmptySpace emptySpace;
    return &emptySpace;
}
