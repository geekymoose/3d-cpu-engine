#ifndef ENGINE_RENDER_SDL2_DRAW_HELPER_H_
#define ENGINE_RENDER_SDL2_DRAW_HELPER_H_

#include <SDL2/SDL.h>


/**
 * Abstract class for Drawing utilities with SDL2.
 *
 * Note: for performance, none of these functions actually lock the surface.
 */
class SDL2DrawHelper {
    private:
        SDL2DrawHelper();

    public:
        static void clearSurface(SDL_Surface* surface);
};


#endif // End header guard



