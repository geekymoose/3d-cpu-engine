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

// TODO To clean
// Vertices must be ordonated
// P1 has lower y, P2 and P3 has same y and highter
static void drawScanlineBottomFlatTriangle(SDL_Renderer* renderer, int p1_x, int p1_y, int p2_x, int p2_y, int p3_x, int p3_y, int w, int h) {
    // Just for readability
    typedef struct { int x; int y; } P;
    P P1 = {p1_x, p1_y};
    P P2 = {p2_x, p2_y};
    P P3 = {p3_x, p3_y};
    const float invSlopeP1P2 = (P2.x - P1.x) / (float)(P2.y - P1.y);
    const float invSlopeP1P3 = (P3.x - P1.x) / (float)(P3.y - P1.y);
    float sx = P1.x, ex = P2.x;
    for(int y = P1.y; y <= P2.y; y++) {
        for(int x = sx; x <= ex; x++) {
            DrawSDLUtils::drawClippedPoint(renderer, (int)x, y, w, h);
        }
        sx += invSlopeP1P2;
        ex += invSlopeP1P3;
    }
}

// TODO To clean
// Vertices must be ordonated
// P1 has lower y, P2 and P3 has same y and highter
static void drawScanlineTopFlatTriangle(SDL_Renderer* renderer, int p1_x, int p1_y, int p2_x, int p2_y, int p3_x, int p3_y, int w, int h) {
    // Just for readability
    typedef struct { int x; int y; } P;
    P P1 = {p1_x, p1_y};
    P P2 = {p2_x, p2_y};
    P P3 = {p3_x, p3_y};
    const float invSlopeP1P2 = (P2.x - P1.x) / (float)(P2.y - P1.y);
    const float invSlopeP1P3 = (P3.x - P1.x) / (float)(P3.y - P1.y);
    float sx = P1.x, ex = P2.x;
    for(int y = P1.y; y >= P2.y; y--) {
        for(int x = sx; x <= ex; x++) {
            DrawSDLUtils::drawClippedPoint(renderer, (int)x, y, w, h);
        }
        sx += invSlopeP1P2;
        ex += invSlopeP1P3;
    }
}

void DrawSDLUtils::drawScanLineTriangle(SDL_Renderer* renderer, int p1_x, int p1_y, int p2_x, int p2_y, int p3_x, int p3_y, int w, int h) {
    // Just for readability
    typedef struct { int x; int y; } P;
    P P1 = {p1_x, p1_y};
    P P2 = {p2_x, p2_y};
    P P3 = {p3_x, p3_y};

    // After that, P1 has lower y value and P3 has higher y value.
    if(P1.y > P2.y) {
        P tmp = P1;
        P1 = P2;
        P2 = tmp;
    }
    if(P2.y > P3.y) {
        P tmp = P2;
        P2 = P3;
        P3 = tmp;
    }
    if(P1.y > P2.y) {
        P tmp = P1;
        P1 = P2;
        P2 = tmp;
    }

    if(P2.y == P3.y){
        if(P2.y > P1.y) {
            drawScanlineBottomFlatTriangle(renderer, P1.x, P1.y, P2.x, P2.y, P3.x, P3.y, w, h);
        }
        else {
            drawScanlineTopFlatTriangle(renderer, P1.x, P1.y, P2.x, P2.y, P3.x, P3.y, w, h);
        }
    }
    else {
        // TODO
    }
}

void DrawSDLUtils::drawClippedPoint(SDL_Renderer* renderer, int x, int y, int w, int h) {
    if(x >= 0 && x <= w && y >= 0 && y <= h) {
        SDL_RenderDrawPoint(renderer, x, y);
    }
}
