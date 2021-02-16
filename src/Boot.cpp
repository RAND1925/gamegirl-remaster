//
// Created by dell on 2019/6/13.
//

#include "../include/Boot.h"
#include "../include/Exceptions.h"

bool Boot::accepts(Word address) const {
    return address < 0x100;
}

Byte Boot::getByte(Word address) const {
    return bios[address];
}

void Boot::setByte(Word address, Byte value) {}
