#ifndef ENGINE_CORE_ENGINE_H_
#define ENGINE_CORE_ENGINE_H_

#include <SDL2/SDL.h>
#include "render/AppWindow.h"
#include "render/SDL2/AppWindowSDL2.h"


// TODO Probably to change later
// Default window value
#define WINDOW_DEFAULT_SIZE_W 960
#define WINDOW_DEFAULT_SIZE_H 540

/**
 * The core engine that runs the rendering.
 */
class Engine {
    private:
        bool isRunning;
        AppWindowSDL2 renderWindow;

    public:
        Engine();

    public:
        bool init();
        bool startRendering();
        bool stopRendering();
        void destroy();

    private:
        bool renderOneFrame();
        void handleEvent(SDL_Event* sdlevent);
};


#endif // End header



