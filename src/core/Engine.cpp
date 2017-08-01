#include "core/Engine.h"


Engine::Engine() : renderWindow() {
    this->isRunning = false;
}

//------------------------------------------------------------------------------
// Body function (Execution)
//------------------------------------------------------------------------------

bool Engine::init(){
    //Init SDL
    // TODO To export from Engine to a general 'init manager' or something like
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::clog << "[ERR] Unable to init Window. SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    renderWindow.initialize("3D soft Engine", WINDOW_DEFAULT_SIZE_W, WINDOW_DEFAULT_SIZE_H);
    renderWindow.show();
    return true;
}

void destroy(){
    SDL_Quit();
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
    // TODO Texture may be not used finally (To delete later)
    SDL_Renderer*   renderer    = this->renderWindow.sdl_renderer;
    //SDL_Texture*    texture     = this->renderWindow.sdl_texture;
    //SDL_UpdateTexture(texture, NULL, pixels, w * format);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    //SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
    return true;
}

void Engine::renderAll(Camera camera, std::vector<Mesh> meshes) {
    for (std::vector<Mesh>::iterator it = meshes.begin(); it != meshes.end(); it++) {
    }
}

bool Engine::stopRendering(){
    this->isRunning = false;
    return true;
}

void Engine::handleEvent(SDL_Event* sdlevent){
    if (sdlevent->type == SDL_QUIT){
        this->stopRendering();
    }
}



