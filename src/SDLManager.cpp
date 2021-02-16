//
// Created by dell on 2019/6/6.
//

#include "SDLManager.h"
#include "Logger.h"

struct Color{
    Byte r, g, b, a;
};
Color realColorMap[5][4]{{
         {0xFF, 0xFF, 0xFF, 0x00},
         {0xAA, 0xAA, 0xAA, 0x55},
         {0x55, 0x55, 0x55, 0xAA},
         {0x00, 0x00, 0x00, 0xFF}
     },
     {
         {0xFF, 0xFA, 0xCD, 0x00},
         {0xFF, 0xCA, 0x28, 0x55},
         {0xFF, 0x00, 0x00, 0xAA},
         {0x00, 0x00, 0x00, 0xFF}
     },
     {
         {0xE0, 0xFF, 0xFF, 0x00},
         {0x6B, 0xC2, 0x35, 0x55},
         {0x06, 0x80, 0x43, 0xAA},
         {0x00, 0x00, 0x00, 0xFF}
     },
     {
         {0xFF, 0xE1, 0xFF, 0x00},
         {0xFF, 0xBB, 0xFF, 0x55},
         {0xBB, 0xFF, 0xFF, 0xAA},
         {0x00, 0x00, 0x00, 0xFF}
     },
     {
         {0x00, 0x00, 0x00, 0x00},
         {0xFF, 0xCA, 0x28, 0x55},
         {0xEE, 0xEE, 0x00, 0xAA},
         {0xFF, 0xFF, 0xFF, 0xFF}
     }
};
void SDLManager::refreshWindow(){
#ifndef NLOG
    logger << "REFRESH!" << std::endl;
#endif
    SDL_UpdateTexture(texture, nullptr, tmp, WINDOW_WIDTH * sizeof (uint32_t));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
    fpsTimer = SDL_GetTicks();
}

SDLManager::~SDLManager(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(texture);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

Uint32 SDLManager::mapColor(Byte grayCode) {
    Color color = realColorMap[colorMapChoice][grayCode];
    return SDL_MapRGBA(format, color.r, color.g, color.b, color.a);
}

void SDLManager::setLine(Byte lineNum, Uint32 *line) {
    std::copy(line, line + 160, tmp + lineNum * 160);
}


bool SDLManager::handleInput() {
    while (SDL_PollEvent(&e)) {
#ifndef NLOG
        logger << "input:" << e.type<< std::endl;
#endif
        if (e.type == SDL_QUIT)
            return true;
        if (e.type == SDL_KEYUP) {
            switch (e.key.keysym.sym) {
                case SDLK_ESCAPE:
                    return true;
                    //for column 1
                case kR:
                    setBit<0>(joypadC1);
                    break;
                case kL:
                    setBit<1>(joypadC1);
                    break;
                case kU:
                    setBit<2>(joypadC1);
                    break;
                case kD:
                    setBit<3>(joypadC1);
                    break;

                    //for column 0
                case kA:
                    setBit<0>(joypadC0);
                    break;
                case kB:
                    setBit<1>(joypadC0);
                    break;
                case kSel:
                    setBit<2>(joypadC0);
                    break;
                case kSta:
                    setBit<3>(joypadC0);
                    break;
            }
        } else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_ESCAPE:
                    return true;
                //for column 1
                case kR:
                    resetBit<0>(joypadC1);
                    break;
                case kL:
                    resetBit<1>(joypadC1);
                    break;
                case kU:
                    resetBit<2>(joypadC1);
                    break;
                case kD:
                    resetBit<3>(joypadC1);
                    break;

                    //for column 0
                case kA:
                    resetBit<0>(joypadC0);
                    break;
                case kB:
                    resetBit<1>(joypadC0);
                    break;
                case kSel:
                    resetBit<2>(joypadC0);
                    break;
                case kSta:
                    resetBit<3>(joypadC0);
                    break;
                default:
                    break;
            }
        } else {
            continue;
        }
    }
    return isQuit;
    //the return value is used to determine if it's end
}

Byte SDLManager::getJoypad(Byte in) {
    in &= 0xF0u;
    if (!getBit<4>(in)){
        in |= (joypadC1 & 0x0Fu);
    }
    if (!getBit<5>(in)){
        in |= (joypadC0 & 0x0Fu);
    }
    return in;
}

void SDLManager::changeColor(int choice = 0) {
    colorMapChoice = choice;
}
void SDLManager::init(const std::string &title_window, int zoomTime, int xPos, int yPos, int fps) {

    this->zoomTime = zoomTime;
    this->xPos = xPos;
    this->yPos = yPos;
    this->fps = fps;
    this->zoomTime = zoomTime;
    int initRes = SDL_Init(SDL_INIT_EVERYTHING);
    if (initRes < 0){
        throw SDLException("init");
    }
    window = SDL_CreateWindow(title_window.c_str(),
                              xPos,
                              yPos,
                              WINDOW_WIDTH * zoomTime,
                              WINDOW_HEIGHT * zoomTime, SDL_WINDOW_SHOWN);
    if (window == nullptr){
        throw SDLException("window create");
    }
    renderer = SDL_CreateRenderer(window,
                                  -1,
                                  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    texture = SDL_CreateTexture(renderer,
                                SDL_PIXELFORMAT_RGBA8888,
                                SDL_TEXTUREACCESS_STREAMING,
                                WINDOW_WIDTH,
                                WINDOW_HEIGHT);
    format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
}

SDLManager *SDLManager::getSDLManager() {
    static SDLManager sdlManager;
    return &sdlManager;
};

