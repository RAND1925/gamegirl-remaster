//
// Created by dell on 2019/6/5.
//

#include "../include/ZRam.h"


bool ZRam::accepts(Word address) const {
    return address >= offset && address < offset + length;
}

Byte ZRam::getByte(Word address) const {
    return  bytes[address - offset];
}

void ZRam::setByte(Word address, Byte value) {
    bytes[address - offset] = value;
}

ZRam *ZRam::getZRam() {
    static ZRam zRam;
    return &zRam;
}
