#include "render/SDL2/AppWindowSDL2.h"


//------------------------------------------------------------------------------
// Constructors - Destructor
//------------------------------------------------------------------------------
AppWindowSDL2::AppWindowSDL2() : AppWindow() {
    this->sdl_window    = NULL;
    this->sdl_renderer  = NULL;
    this->sdl_texture   = NULL;
}


//------------------------------------------------------------------------------
// General functions
//------------------------------------------------------------------------------

void AppWindowSDL2::initialize(const char* name, const int w, const int h) {
    return this->initialize(name, w, h, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED);
}

// TODO To update: At the moment, flags is hard coded (To SDL_WINDOW_HIDDEN)
void AppWindowSDL2::initialize(const char* title, const int w, const int h, const int l, const int t) {
    // Load sdl_window
    this->sdl_window = SDL_CreateWindow(title, l, t, w, h, SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE);
    if(this->sdl_window == NULL){
        std::clog << "[ERR] Unable to start SDL window. SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }
    // Load sdl_renderer
    this->sdl_renderer = SDL_CreateRenderer(this->sdl_window, -1, 0);
    if(this->sdl_renderer == NULL){
        std::clog << "[ERR] Unable to start SDL window. SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }
    // Load texture
    this->sdl_texture = SDL_CreateTexture( this->sdl_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, w, h);
    if(this->sdl_texture == NULL){
        std::clog << "[ERR] Unable to start SDL window. SDL_Error: " << SDL_GetError() << std::endl;
        return;
    }
}

void AppWindowSDL2::show() {
    SDL_ShowWindow(this->sdl_window);
}

void AppWindowSDL2::hide() {
    SDL_HideWindow(this->sdl_window);
}

void AppWindowSDL2::destroy() {
    SDL_DestroyTexture(this->sdl_texture);
    SDL_DestroyRenderer(this->sdl_renderer);
    SDL_DestroyWindow(this->sdl_window);
    this->sdl_texture   = NULL;
    this->sdl_renderer  = NULL;
    this->sdl_window    = NULL;
}

void AppWindowSDL2::maximize() {
    SDL_MaximizeWindow(this->sdl_window);
}

void AppWindowSDL2::minimize() {
    SDL_MinimizeWindow(this->sdl_window);
}


//------------------------------------------------------------------------------
// Getter / Setters / Data
//------------------------------------------------------------------------------
const char* AppWindowSDL2::getName() const {
    return SDL_GetWindowTitle(this->sdl_window);
}

void AppWindowSDL2::setName(const char* value) {
    SDL_SetWindowTitle(this->sdl_window, value);
}

void AppWindowSDL2::getSize(int* x, int* y) const {
    SDL_GetWindowSize(sdl_window, x, y);
}

void AppWindowSDL2::getPosition(int* left, int* top) const {
    SDL_GetWindowPosition(sdl_window, left, top);
}
