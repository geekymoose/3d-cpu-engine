#ifndef ENGINE_RENDER_SDL_H_
#define ENGINE_RENDER_SDL_H_

#include <SDL2/SDL.h>

/**
 *
 * \note
 * These functions are mainly already implemented by SDL (And probably way better).
 * It is for the pure learning purpose.
 *
 * \see https://wiki.libsdl.org/SDL_RenderDrawLine
 */
class DrawSDLUtils {

    public:
        /**
         * Draw a line using Digital Differential Analyzer algorithm (DDA).
         *
         * \note
         * This isn't the most efficient algorithm since it still use one
         * floating point operation per pixel.
         * (But still better than naive algorithm that uses 2 floating-point operations
         * per pixel).
         */
        static void drawLineDDA(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, int w, int h);

        static void drawClippedPoint(SDL_Renderer* renderer, int x, int y, int w, int h);
};

#endif // Header guard



