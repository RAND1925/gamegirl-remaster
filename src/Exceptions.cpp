#include <utility>

#include <utility>

#include <utility>

#include <utility>

//
// Created by dell on 2019/6/16.
//
#include "SDL.h"
#include "Exceptions.h"

SDLException::SDLException(std::string msg) : _msg(std::move(msg)){
#ifndef NLOG
    logger << _msg<< " " << SDL_GetError() << std::endl;
#endif
}

FileNotFoundException::FileNotFoundException(std::string msg, const std::string path) : _msg{std::move(msg)}, _path{path}{
#ifndef NLOG
    logger << "ERROR: " << _msg << " path: " << path << std::endl;
#endif
}

