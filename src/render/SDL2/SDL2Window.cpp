#include "render/SDL2/SDL2Window.h"


//------------------------------------------------------------------------------
// Constructors - Destructor
//------------------------------------------------------------------------------
SDL2Window::SDL2Window(){
    this->window    = NULL;
    this->renderer  = NULL;
    this->texture   = NULL;
    this->width     = 0;
    this->height    = 0;
    this->left      = SDL_WINDOWPOS_UNDEFINED;
    this->top       = SDL_WINDOWPOS_UNDEFINED;
}


//------------------------------------------------------------------------------
// Body function (Initialization - Stop)
//------------------------------------------------------------------------------

bool SDL2Window::showWindow(const char* title, const int w, const int h) {
    return this->showWindow(title, w, h, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED);
}

bool SDL2Window::showWindow(const char* title, const int w, const int h, const int l, const int t) {
    // Set values
    this->window    = NULL;
    this->renderer  = NULL;
    this->texture   = NULL;
    this->width     = w;
    this->height    = h;
    this->left      = l;
    this->top       = t;

    // Create window
    this->window = SDL_CreateWindow(title, left, top, width, height, SDL_WINDOW_SHOWN);
    if(this->window == NULL){
        std::clog << "[ERR] Unable to start SDL window. SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Load renderer
    this->renderer = SDL_CreateRenderer(this->window, -1, 0);
    if(this->renderer == NULL){
        std::clog << "[ERR] Unable to start SDL window. SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Load Back Buffer
    this->texture = SDL_CreateTexture(
            this->renderer,
            SDL_PIXELFORMAT_ARGB8888,
            SDL_TEXTUREACCESS_STATIC,
            this->width,
            this->height);
    if(this->texture == NULL){
        std::clog << "[ERR] Unable to start SDL window. SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

bool SDL2Window::closeWindow(){
    SDL_DestroyTexture(this->texture);
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
    this->window = NULL;
    this->renderer = NULL;
    return true;
}



