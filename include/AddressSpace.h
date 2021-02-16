// an abstract class, each part which require to access memory should derive it
// Created by dell on 2019/5/7.
//



#ifndef CPPGB_ADDRESSSPACE_H
#define CPPGB_ADDRESSSPACE_H

#include"common.h"
class AddressSpace {
public:
    [[nodiscard]] virtual bool accepts(Word address) const = 0;
    [[nodiscard]] virtual Byte getByte(Word address) const = 0;
    virtual void setByte(Word address, Byte value) = 0;
};


#endif //GAMEGIRL_ADDRESSSPACE_H
