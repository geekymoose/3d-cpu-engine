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
        renderOneFrame();
        while(SDL_PollEvent(&sdlevent)){
            handleEvent(&sdlevent);
        }
    }
    return true;
}

bool Engine::renderOneFrame(){
    SDL_RenderClear(this->window.renderer);
    SDL_RenderPresent(this->window.renderer);
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



