#include "render/SDL2/SDL2Window.h"


//------------------------------------------------------------------------------
// Constructors - Destructor
//------------------------------------------------------------------------------
SDL2Window::SDL2Window(){
    this->window    = NULL;
    this->screen    = NULL;
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
    this->screen    = NULL;
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

    // Load SDL_Surface from the window
    this->screen = SDL_GetWindowSurface(window);
    SDL_FillRect(this->screen, NULL, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));
    SDL_UpdateWindowSurface(this->window);
    return true;
}

bool SDL2Window::closeWindow(){
    SDL_FreeSurface(screen);
    SDL_DestroyWindow(window);
    SDL_Quit();
    this->window = NULL;
    this->screen = NULL;
    return true;
}
