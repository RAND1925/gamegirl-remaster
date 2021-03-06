//
// Created by dell on 2019/6/5.
//
#include "../include/WRam.h"


bool WRam::accepts(Word address) const {
    return address >= offset && address < offset + length;
}
Byte WRam::getByte(Word address) const {
    return  bytes[address & 0x1FFF];
}

void WRam::setByte(Word address, Byte value) {
    bytes[address & 0x1FFF] = value;
}

WRam *WRam::getWRam() {
    static WRam wRam;
    return &wRam;
}
