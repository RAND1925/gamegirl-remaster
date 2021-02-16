// Cartridge and ex-ram
// Created by dell on 2019/6/3.
//

#ifndef GAMEGIRL_Cartridge_H
#define GAMEGIRL_Cartridge_H

#include <string>
#include <fstream>
#include <memory>
#include "common.h"
#include "AddressSpace.h"
#include "Cartridges/Cartridge.h"
#include "Cartridges/Cartridge_ROM0.h"
#include "Cartridges/Cartridge_MBC1.h"


class CartridgeDriver final : public AddressSpace {
public:
    void openFile(const std::string &filePath);

    // void reopenFile(const std::string &filePath);

    const std::string &getTitle() const;

    ~CartridgeDriver();

    static CartridgeDriver *getCartridgeDriver() {
        static CartridgeDriver cartridgeDriver;
        return &cartridgeDriver;
    }

    void loadCartridge();

protected:
    CartridgeDriver() = default;

private:
    std::unique_ptr<Cartridge> cartridge;
    Byte cartridgeType{};
    Byte romBankCode{};
    Byte ramBankCode{};
    size_t romSize{};
    size_t ramSize{};
    std::string title;
    std::string filePath;
    int ramSizeMap[5] = {0, 2, 8, 32, 128};
    int romSizeMap[3] = {72, 80, 96};

    bool accepts(Word address) const override;

    Byte getByte(Word address) const override;

    void setByte(Word address, Byte value) override;

#endif //GAMEGIRL_Cartridge_H
};