#include "render/SDL2/DrawSDLUtils.h"

void DrawSDLUtils::drawLineDDA(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, int w, int h) {
    float dx    = x2 - x1;
    float dy    = y2 - y1;
    float m     = dy / dx;
    if(m <= 1 && m >= -1) {
        int x_start = x1;
        int x_end   = x2;
        float y     = y1;
        // This is used to start drawing from the point with lower x value.
        if(dx < 0) {
            x_start = x2;
            x_end   = x1;
            y       = y2;
        }
        for(int x = x_start; x <= x_end; x++) {
            y += m;
            DrawSDLUtils::drawClippedPoint(renderer, x, (int)y, w, h);
        }
    }
    else {
        m = dx / dy;
        int y_start = y1;
        int y_end   = y2;
        float x     = x1;
        // This is used to start drawing from the point with lower y value.
        if(dy < 0) {
            y_start = y2;
            y_end   = y1;
            x       = x2;
        }
        for(int y = y_start; y <= y_end; y++) {
            x += m;
            DrawSDLUtils::drawClippedPoint(renderer, x, (int)y, w, h);
        }
    }
}

void DrawSDLUtils::drawLineMidpoint(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, int w, int h) {
    // TODO
}

void DrawSDLUtils::drawClippedPoint(SDL_Renderer* renderer, int x, int y, int w, int h) {
    if(x >= 0 && x <= w && y >= 0 && y <= h) {
        SDL_RenderDrawPoint(renderer, x, y);
    }
}
