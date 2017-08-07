#include "render/SDL2/DrawSDLUtils.h"

void DrawSDLUtils::drawLineDDA(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, int w, int h) {
    float dx    = x2 - x1;
    float dy    = y2 - y1;
    float m     = dy / dx;
    float y     = 0.0f;
    int x_start = 0;
    int x_end   = 0;
    // This is used to start drawing from the point with lower x value.
    if(dx >= 0) {
        x_start = x1;
        x_end   = x2;
        y       = y1;
    }
    else {
        x_start = x2;
        x_end   = x1;
        y       = y2;
    }
    for(int x = x_start; x <= x_end; x++) {
        y += m;
        DrawSDLUtils::drawClippedPoint(renderer, x, (int)y, w, h);
    }
}

void DrawSDLUtils::drawClippedPoint(SDL_Renderer* renderer, int x, int y, int w, int h) {
    if(x >= 0 && x <= w && y >= 0 && y <= h) {
        SDL_RenderDrawPoint(renderer, x, y);
    }
}
