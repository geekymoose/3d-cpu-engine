#include "core/Engine.h"


Engine::Engine(){
    this->isRunning = false;
}

//------------------------------------------------------------------------------
// Body function (Execution)
//------------------------------------------------------------------------------

bool Engine::init(){
    //Init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::clog << "[ERR] Unable to init Window. SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    return window.showWindow("3D soft Engine", 960, 540);
}

bool Engine::startRendering(){
    if(isRunning){
        return false;
    }
    this->isRunning = true;
    // Main loop
    SDL_Event sdlevent;
    while(isRunning){
        while(SDL_PollEvent(&sdlevent)){
            handleEvent(&sdlevent);
        }
        renderOneFrame();
    }
    return true;
}

bool Engine::renderOneFrame(){
    // Refresh background to white
    // SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
    // SDL_UpdateWindowSurface(window);
    return true;
}

bool Engine::stopRendering(){
    this->isRunning = false;
    this->window.closeWindow();
    return true;
}

void Engine::handleEvent(SDL_Event* sdlevent){
    if (sdlevent->type == SDL_QUIT){
        this->stopRendering();
    }
}
