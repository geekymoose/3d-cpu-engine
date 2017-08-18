#include "render/SDL2/DrawSDLUtils.h"


// -----------------------------------------------------------------------------
// Static functions
// -----------------------------------------------------------------------------

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
    float sx = P1.x, ex = P1.x;
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
    float sx = P1.x, ex = P1.x;
    for(int y = P1.y; y >= P2.y; y--) {
        for(int x = sx; x <= ex; x++) {
            DrawSDLUtils::drawClippedPoint(renderer, (int)x, y, w, h);
        }
        sx -= invSlopeP1P2;
        ex -= invSlopeP1P3;
    }
}


// -----------------------------------------------------------------------------
// Class functions
// -----------------------------------------------------------------------------

void DrawSDLUtils::drawLine(SDL_Renderer* renderer, VectF3 const& p1, VectF3 const& p2, int w, int h) {
    const float x1 = p1.x * w + w / 2.0f;
    const float x2 = p2.x * w + w / 2.0f;
    const float y1 = p1.y * h + h / 2.0f;
    const float y2 = p2.y * h + h / 2.0f;
    DrawSDLUtils::drawLineDDA(renderer, x1, y1, x2, y2, w, h);
}

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

void DrawSDLUtils::drawFilledTriangle(SDL_Renderer* renderer,
                                        float *depthBuffer,
                                        VectF3 const& p1,
                                        VectF3 const& p2,
                                        VectF3 const& p3,
                                        int w, int h) {
    const float x1 = p1.x * w + w / 2.0f;
    const float x2 = p2.x * w + w / 2.0f;
    const float x3 = p3.x * w + w / 2.0f;
    const float y1 = p1.y * h + h / 2.0f;
    const float y2 = p2.y * h + h / 2.0f;
    const float y3 = p3.y * h + h / 2.0f;
    //DrawSDLUtils::drawScanLineTriangle(renderer, x1, y1, x2, y2, x3, y3, w, h);
    DrawSDLUtils::drawScanLineTriangle(renderer, depthBuffer, x1, y1, p1.z, x2, y2, p2.z, x3, y3, p3.z, w, h);
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
        const float invSlopeP1P3 = (P3.x - P1.x) / (float)(P3.y - P1.y);
        P P4;
        P4.y = P2.y;
        P4.x = invSlopeP1P3 * (P2.y - P3.y) + P3.x;

        // P4 at the right of P2
        if(P4.x > P2.x) {
            drawScanlineBottomFlatTriangle(renderer, P1.x, P1.y, P2.x, P2.y, P4.x, P4.y, w, h);
            drawScanlineTopFlatTriangle(renderer, P3.x, P3.y, P2.x, P2.y, P4.x, P4.y, w, h);
        }
        else {
            drawScanlineBottomFlatTriangle(renderer, P1.x, P1.y, P4.x, P4.y, P2.x, P2.y, w, h);
            drawScanlineTopFlatTriangle(renderer, P3.x, P3.y, P4.x, P4.y, P2.x, P2.y, w, h);
        }
    }
}

static float interpolate(const float min, const float max, const float gradient) {
    return min + (max - min) * gradient;
}

// Draw line between 2 points, at y position, from left to right.
// Points are start point (On line p1p2) and end point (On line p3p4);
// p1p2 is at the left, p3p4 at the right
static void drawOneScanLineTriangle(SDL_Renderer* renderer,
                                float *depthBuffer,
                                int y,
                                int p1_x, int p1_y, float p1_z,
                                int p2_x, int p2_y, float p2_z,
                                int p3_x, int p3_y, float p3_z,
                                int p4_x, int p4_y, float p4_z,
                                int w, int h) {
    float gradientP1P2 = ((p2_y - p1_y) != 0) ? (y - p1_y) / (float)(p2_y - p1_y) : 1;
    float gradientP3P4 = ((p4_y - p3_y) != 0) ? (y - p3_y) / (float)(p4_y - p3_y) : 1;

    float sx = interpolate(p1_x, p2_x, gradientP1P2);
    float ex = interpolate(p3_x, p4_x, gradientP3P4);

    float z1 = interpolate(p1_z, p2_z, gradientP1P2);
    float z2 = interpolate(p3_z, p4_z, gradientP3P4);

    for(int x = sx; x <= ex; x++) {
        int index = y * w + x;
        float gradientz = (x - sx) / (float)(ex - sx);
        float z = interpolate(z1, z2, gradientz);
        if(depthBuffer[index] > z) {
            depthBuffer[index] = z;
            DrawSDLUtils::drawClippedPoint(renderer, x, y, w, h);
        }
    }
}

void DrawSDLUtils::drawScanLineTriangle(SDL_Renderer* renderer,
                                        float *depthBuffer,
                                        int p1_x, int p1_y, float p1_z,
                                        int p2_x, int p2_y, float p2_z,
                                        int p3_x, int p3_y, float p3_z,
                                        int w, int h) {
    // Just for readability
    typedef struct { int x; int y; float z; } P;
    P P1 = {p1_x, p1_y, p1_z};
    P P2 = {p2_x, p2_y, p2_z};
    P P3 = {p3_x, p3_y, p3_z};

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

    float invSlopeP1P2 = (P2.y - P1.y > 0) ? (P2.x - P1.x) / (float)(P2.y - P1.y) : 0;
    float invSlopeP1P3 = (P3.y - P1.y > 0) ? (P3.x - P1.x) / (float)(P3.y - P1.y) : 0;

    // P2 at the right of P1P3
    if(invSlopeP1P2 > invSlopeP1P3) {
        for(int y = P1.y; y <= P3.y; y++) {
            if(y < P2.y) {
                drawOneScanLineTriangle(renderer, depthBuffer, y,
                        P1.x, P1.y, P1.z,
                        P3.x, P3.y, P3.z,
                        P1.x, P1.y, P1.z,
                        P2.x, P2.y, P2.z,
                        w, h);
            }
            else {
                drawOneScanLineTriangle(renderer, depthBuffer, y,
                        P1.x, P1.y, P1.z,
                        P3.x, P3.y, P3.z,
                        P2.x, P2.y, P2.z,
                        P3.x, P3.y, P3.z,
                        w, h);
            }
        }
    }
    // P2 at the left of P1P3
    else {
        for(int y = P1.y; y <= P3.y; y++) {
            if(y < P2.y) {
                drawOneScanLineTriangle(renderer, depthBuffer, y,
                        P1.x, P1.y, P1.z,
                        P2.x, P2.y, P2.z,
                        P1.x, P1.y, P1.z,
                        P3.x, P3.y, P3.z,
                        w, h);
            }
            else {
                drawOneScanLineTriangle(renderer, depthBuffer, y,
                        P2.x, P2.y, P2.z,
                        P3.x, P3.y, P3.z,
                        P1.x, P1.y, P1.z,
                        P3.x, P3.y, P3.z,
                        w, h);
            }
        }
    }
}

void DrawSDLUtils::drawClippedPoint(SDL_Renderer* renderer, int x, int y, int w, int h) {
    if(x >= 0 && x <= w && y >= 0 && y <= h) {
        SDL_RenderDrawPoint(renderer, x, y);
    }
}
