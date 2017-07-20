#include "core/Engine.h"


Engine::Engine() : backbuffer() {
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
    return window.showWindow("3D soft Engine", WINDOW_WIDTH, WINDOW_HEIGHT); // Open SDL Window
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
    // Last value is the pitch. Here, pixel are 32 bits of size so pitch is 4bytes * width
    SDL_UpdateTexture(this->window.texture, NULL, this->backbuffer, this->window.width * sizeof(int));
    SDL_RenderClear(this->window.renderer);
    SDL_RenderCopy(this->window.renderer, this->window.texture, NULL, NULL);
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



