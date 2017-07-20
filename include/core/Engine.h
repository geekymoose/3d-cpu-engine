#ifndef ENGINE_CORE_ENGINE_H_
#define ENGINE_CORE_ENGINE_H_

#include <SDL2/SDL.h>
#include "render/SDL2/SDL2Window.h"
#include "render/SDL2/SDL2DrawHelper.h"

// TODO: works for now, but we can't resize window then
#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 540

/**
 * The core engine that runs the rendering.
 */
class Engine {
    private:
        bool isRunning;
        SDL2Window window;
        int backbuffer[WINDOW_WIDTH * WINDOW_HEIGHT]; // TODO Assumed to be 32 bits of size for now

    public:
        Engine();

    public:
        bool init();
        bool startRendering();
        bool stopRendering();

    private:
        bool renderOneFrame();
        void handleEvent(SDL_Event* sdlevent);
};


#endif // End header



