#pragma once

#include <SDL2/SDL.h>
#include "math/VectF3.h"

/**
 *
 * \note
 * TODO This class is temporary and will be re factored.
 * (Design pattern strategy + Factory for instance, to be able to switch used algorithm.)
 *
 * \note
 * These functions are mainly already implemented by SDL (And probably way better).
 * It is for the pure learning purpose.
 *
 * \see https://wiki.libsdl.org/SDL_RenderDrawLine
 */
class DrawSDLUtils {

    public:
        static void drawLine(SDL_Renderer* renderer, VectF3 const& p1, VectF3 const& p2, int w, int h);
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

        static void drawScanLineTriangle(SDL_Renderer* renderer, int p1_x, int p1_y, int p2_x, int p2_y, int p3_x, int p3_y, int w, int h);

        static void drawFilledTriangle(SDL_Renderer* renderer,
                                    float *depthBuffer,
                                    VectF3 const& p1,
                                    VectF3 const& p2,
                                    VectF3 const& p3,
                                    int w, int h);

        static void drawScanLineTriangle(SDL_Renderer* renderer,
                                        float *depthBuffer,
                                        int p1_x, int p1_y, float p1_z,
                                        int p2_x, int p2_y, float p2_z,
                                        int p3_x, int p3_y, float p3_z,
                                        int w, int h);


        static void drawClippedPoint(SDL_Renderer* renderer, int x, int y, int w, int h);
};

