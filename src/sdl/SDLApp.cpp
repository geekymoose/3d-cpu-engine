#include "sdl/SDLApp.h"


//------------------------------------------------------------------------------
// Constructors - Destructor
//------------------------------------------------------------------------------
SDLApp::SDLApp() {
    this->window = NULL;
    this->screen = NULL;
    std::clog << "[INFO] Create SDL application." << std::endl;
    isRunning = false;
}

SDLApp::~SDLApp() {
    std::clog << "[INFO] Destroys application." << std::endl;
}


//------------------------------------------------------------------------------
// Body function (Initialization - Stop)
//------------------------------------------------------------------------------
bool SDLApp::runApp(){
    //App should not be already running
    if(isRunning){
        std::clog << "[Warning] Application already running..." << std::endl;
        return false;
    }

    if( this->window ==  NULL || this->screen == NULL){
        std::clog << "[ERR] Unable to run application (Init failed)..." << std::endl;
        return false;
    }
    isRunning = true;

    //Main execution loop
    SDL_Event sdlevent;
    while(isRunning){
        while(SDL_PollEvent(&sdlevent)){
            doEvent(&sdlevent);
        }
        doLoop();
        doRender();
    }
    return 0;
}

bool SDLApp::initApp(){
    //Init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::clog << "[ERR] Unable to init App. SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    //TODO Currently hard coded values
    //Create SDL window for screen
    this->window = SDL_CreateWindow(
        "3D Soft Engine",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        960,
        540,
        SDL_WINDOW_SHOWN
    );

    if(window == NULL){
        std::clog << "[ERR] Unable to start SDL window. SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    //Load SDL_Surface from the window
    screen = SDL_GetWindowSurface(window);
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));
    SDL_UpdateWindowSurface(window);
    return true;
}

bool SDLApp::closeApp(){
    this->isRunning = false;
    SDL_FreeSurface(screen);
    SDL_DestroyWindow(window);
    SDL_Quit();
    this->window = NULL;
    this->screen = NULL;
    return true;
}


//------------------------------------------------------------------------------
// Body function (Execution)
//------------------------------------------------------------------------------
void SDLApp::doEvent(SDL_Event* sdlevent){
    //TODO
    if (sdlevent->type == SDL_QUIT){
        this->closeApp();
    }
}

void SDLApp::doLoop(){
    //TODO
}

void SDLApp::doRender(){
    //Refresh background to white
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0x00, 0x00, 0x00));
    SDL_UpdateWindowSurface(window);
}
