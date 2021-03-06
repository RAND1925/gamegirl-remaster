// Created by dell on 2019/6/14.
// 4MHz

#include "../include/Joypad.h"


bool Joypad::accepts(Word address) const {
    return address == 0xFF00;
}

Byte Joypad::getByte(Word address) const {
    return regJoypad;
}
void Joypad::setByte(Word address, Byte value) {
    regJoypad &= 0xCFu;
    regJoypad |= (value & 0x30u);
}

void Joypad::update() {
    Byte newJoypad = SDLManager::getSDLManager()->getJoypad(regJoypad);
    bool needInterrupt = false;
    for (Byte i = 0; i < 4; ++i){
        if (getBit(regJoypad, i) && !(getBit(regJoypad, i))){
            needInterrupt = true;
        }
    }

    if (needInterrupt){
        InterruptManager::getInterruptManager()->requestInterrupt(4);
    }
    regJoypad = newJoypad;

}
