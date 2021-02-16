extern "C" {
    #include "getopt.h"
}
#include <cstdlib>
#include <string>
#include "../include/common.h"
#include "../include/MMU.h"
#include "../include/WRam.h"
#include "../include/ZRam.h"
#include "../include/GPU.h"
#include "../include/Timer.h"
#include "../include/CartridgeDriver.h"
#include "../include/InterruptManager.h"
#include "../include/CPU.h"
#include "../include/SDLManager.h"
#include "../include/Boot.h"
#include "../include/Joypad.h"
#include "../include/EmptySpace.h"
#include "../include/Logger.h"


bool isQuit = false;
uint64_t step();
bool init(int argc, char **argv);
int main(int argc, char **argv) {
    int allCycle = 0;
    bool useBoot = init(argc, argv);
    if (useBoot) {
        while (CPU::getCPU()->getPC() < 0x100) {
            allCycle += step();
        }
        MMU::getMMU()->removeAddressSpace(*Boot::getBoot());
    }
    while (!isQuit) {
        allCycle += step();
#ifndef NLOG
        logger << "clk:" << allCycle << std::endl;
#endif
    }
    return 0;
}


bool init(int argc, char **argv) {
    if (argc == 1) {
        throw FileNotFoundException("argument wrong", "no file path ");
    }
    const std::string FILE_PATH(argv[1]);
    uint16_t fps = 60;
    auto xPos = SDL_WINDOWPOS_UNDEFINED;
    auto yPos = SDL_WINDOWPOS_UNDEFINED;
    uint8_t zoomTime = 1;
    bool useBoot = false;
    bool useSprite = true;
    optind++;
    const std::string optString{"bSf:x:y:z:c:"};
    const char* const optPtr = optString.c_str();
    int option;
    while ((option = getopt(argc, argv, optPtr)) != -1){
        switch (option) {
            case 'b':
                useBoot = true;
                break;
            case 'z':
                zoomTime = std::atoi(optarg);
                break;
            case 'f':
                fps = std::atoi(optarg);
                break;
            case 'x':
                xPos = std::atoi(optarg);
                break;
            case 'y':
                yPos = std::atoi(optarg);
                break;
            case 'S':
                useSprite = false;
                break;
            case 'c': {
                SDLManager::getSDLManager()->changeColor(std::atoi(optarg));
                break;
            }
            default:
                break;
        }
    }
    std::ios::sync_with_stdio(false);
    CartridgeDriver::getCartridgeDriver()->openFile(FILE_PATH);
    SDLManager::getSDLManager()->init(CartridgeDriver::getCartridgeDriver()->getTitle(), zoomTime, xPos, yPos, fps);
    (&GPU::getInstance())->init(useSprite);
    CPU::getCPU()->initMap();
    MMU::getMMU()->init();
#ifndef NLOG
    logger.open("gamegirl.log");
#endif
    if (useBoot){
        MMU::getMMU()->addAddressSpace(* Boot::getBoot());
        CPU::getCPU()->initRegisters();
    } else {
        CPU::getCPU()->initRegistersAfterBoot();
    }
    MMU::getMMU()->addAddressSpace(*CartridgeDriver::getCartridgeDriver());
    MMU::getMMU()->addAddressSpace(*WRam::getWRam());
    MMU::getMMU()->addAddressSpace(*ZRam::getZRam());
    MMU::getMMU()->addAddressSpace(GPU::getInstance());
    MMU::getMMU()->addAddressSpace(*Timer::getTimer());
    MMU::getMMU()->addAddressSpace(*Joypad::getJoypad());
    MMU::getMMU()->addAddressSpace(*InterruptManager::getInterruptManager());
    MMU::getMMU()->addAddressSpace(*EmptySpace::getEmptySpace());
    return useBoot;
}

uint64_t step() {
    isQuit = SDLManager::getSDLManager()->handleInput();
    Joypad::getJoypad()->update();
    Byte cycle = CPU::getCPU()->step();
    Timer::getTimer()->addTime(cycle);
    (&GPU::getInstance())->addTime(cycle);
    return cycle;
};

