#include "render/SDL2/DrawSDLUtils.h"
// TODO DEV NOTE: This file is kind of messy and ugly! I'll clean it oh yeah!


// -----------------------------------------------------------------------------
// Static functions
// -----------------------------------------------------------------------------

// TODO To move in math lib
static float interpolate(const float min, const float max, const float gradient) {
    return min + (max - min) * gradient;
}

// Swap v1 with v2
static void swapVerticeData(VertexData &v1, VertexData &v2) {
    VertexData tmp  = {v1.screenPos, v1.normal, v1.transPos};
    // v1 = v2
    v1.screenPos    = v2.screenPos;
    v1.normal       = v2.normal;
    v1.transPos     = v2.transPos;
    // v2 = tmp
    v2.screenPos    = tmp.screenPos;
    v2.normal       = tmp.normal;
    v2.transPos     = tmp.transPos;
}

static float calCosNormLight(VectF3 const& vertexPos, VectF3 & normal, VectF3 const& lightSource) {
    VectF3 lightDir = lightSource - vertexPos;
    lightDir.normalizeFast();
    normal.normalizeFast();
    return std::max(VectF3::dotProduct(normal, lightDir), 0.0f);
}


// -----------------------------------------------------------------------------
// Draw Line
// -----------------------------------------------------------------------------

void DrawSDLUtils::drawLine(SDL_Renderer* renderer, VectF3 const& p1, VectF3 const& p2, int w, int h) {
    DrawSDLUtils::drawLineDDA(renderer, p1.x, p1.y, p2.x, p2.y, w, h);
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


// -----------------------------------------------------------------------------
// Draw Triangle with Z-Buffering and Flag-shading
// -----------------------------------------------------------------------------

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
                                    int w, int h,
                                    SDL_Color *color) {
    float gradientP1P2 = ((p2_y - p1_y) != 0) ? (y - p1_y) / (float)(p2_y - p1_y) : 1;
    float gradientP3P4 = ((p4_y - p3_y) != 0) ? (y - p3_y) / (float)(p4_y - p3_y) : 1;

    float sx = interpolate(p1_x, p2_x, gradientP1P2);
    float ex = interpolate(p3_x, p4_x, gradientP3P4);

    float z1 = interpolate(p1_z, p2_z, gradientP1P2);
    float z2 = interpolate(p3_z, p4_z, gradientP3P4);

    for(int x = sx; x <= ex; x++) {
        // Skip point outside the screen.
        if(x >= 0 && x < w && y >= 0 && y < h) {
            int index = y * w + x;
            float gradientz = (x - sx) / (float)(ex - sx);
            float z = interpolate(z1, z2, gradientz);
            if(depthBuffer[index] > z) {
                depthBuffer[index] = z;
                SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
    }
}

void DrawSDLUtils::drawScanLineTriangle(SDL_Renderer* renderer,
                                        float *depthBuffer,
                                        VertexData & v1,
                                        VertexData & v2,
                                        VertexData & v3,
                                        int w, int h,
                                        SDL_Color *color) {
    // After that, P1 has lower y value and P3 has higher y value.
    if(v1.screenPos->y > v2.screenPos->y) {
        swapVerticeData(v1, v2);
    }
    if(v2.screenPos->y > v3.screenPos->y) {
        swapVerticeData(v2, v3);
    }
    if(v1.screenPos->y > v2.screenPos->y) {
        swapVerticeData(v1, v2);
    }

    float invSlopeP1P2 = (v2.screenPos->x - v1.screenPos->x) / (float)(v2.screenPos->y - v1.screenPos->y);
    float invSlopeP1P3 = (v3.screenPos->x - v1.screenPos->x) / (float)(v3.screenPos->y - v1.screenPos->y);

    VectF3 lightSource(100, 50, -50); // TODO Hard coded, should be moved outside
    VectF3 faceNormal   = (*v1.normal + *v2.normal + *v3.normal) / 3;
    VectF3 faceCenter   = (*v1.transPos + *v2.transPos + *v3.transPos) / 3;
    float cosNormLight  = calCosNormLight(faceCenter, faceNormal, lightSource);

    // Calculate new color
    color->r *=  cosNormLight;
    color->g *=  cosNormLight;
    color->b *=  cosNormLight;

    // P2 at the right of P1P3
    if(invSlopeP1P2 > invSlopeP1P3) {
        for(int y = v1.screenPos->y; y < v2.screenPos->y; y++) {
            drawOneScanLineTriangle(renderer, depthBuffer, y,
                    v1.screenPos->x, v1.screenPos->y, v1.screenPos->z,
                    v3.screenPos->x, v3.screenPos->y, v3.screenPos->z,
                    v1.screenPos->x, v1.screenPos->y, v1.screenPos->z,
                    v2.screenPos->x, v2.screenPos->y, v2.screenPos->z,
                    w, h, color);
        }
        for(int y = v2.screenPos->y; y <= v3.screenPos->y; y++) {
            drawOneScanLineTriangle(renderer, depthBuffer, y,
                    v1.screenPos->x, v1.screenPos->y, v1.screenPos->z,
                    v3.screenPos->x, v3.screenPos->y, v3.screenPos->z,
                    v2.screenPos->x, v2.screenPos->y, v2.screenPos->z,
                    v3.screenPos->x, v3.screenPos->y, v3.screenPos->z,
                    w, h, color);
        }
    }
    // P2 at the left of P1P3
    else {
        for(int y = v1.screenPos->y; y < v2.screenPos->y; y++) {
            drawOneScanLineTriangle(renderer, depthBuffer, y,
                    v1.screenPos->x, v1.screenPos->y, v1.screenPos->z,
                    v2.screenPos->x, v2.screenPos->y, v2.screenPos->z,
                    v1.screenPos->x, v1.screenPos->y, v1.screenPos->z,
                    v3.screenPos->x, v3.screenPos->y, v3.screenPos->z,
                    w, h, color);
        }
        for(int y = v2.screenPos->y; y <= v3.screenPos->y; y++) {
            drawOneScanLineTriangle(renderer, depthBuffer, y,
                    v2.screenPos->x, v2.screenPos->y, v2.screenPos->z,
                    v3.screenPos->x, v3.screenPos->y, v3.screenPos->z,
                    v1.screenPos->x, v1.screenPos->y, v1.screenPos->z,
                    v3.screenPos->x, v3.screenPos->y, v3.screenPos->z,
                    w, h, color);
        }
    }
}


// -----------------------------------------------------------------------------
// Other functions
// -----------------------------------------------------------------------------

void DrawSDLUtils::drawClippedPoint(SDL_Renderer* renderer, int x, int y, int w, int h) {
    if(x >= 0 && x <= w && y >= 0 && y <= h) {
        SDL_RenderDrawPoint(renderer, x, y);
    }
}


// -----------------------------------------------------------------------------
// Draw Filled triangle (Simple)
// -----------------------------------------------------------------------------

// TODO To clean
// Vertices must be ordonated
// P1 has lower y, P2 and P3 has same y and highter
static void drawScanlineBottomFlatTriangle(SDL_Renderer* renderer,
                                            int p1_x, int p1_y,
                                            int p2_x, int p2_y,
                                            int p3_x, int p3_y,
                                            int w, int h) {
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
static void drawScanlineTopFlatTriangle(SDL_Renderer* renderer,
                                        int p1_x, int p1_y,
                                        int p2_x, int p2_y,
                                        int p3_x, int p3_y,
                                        int w, int h) {
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
void DrawSDLUtils::drawScanLineTriangle(SDL_Renderer* renderer,
                                        int p1_x, int p1_y,
                                        int p2_x, int p2_y,
                                        int p3_x, int p3_y,
                                        int w, int h) {
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


// -----------------------------------------------------------------------------
// Draw Triangle with Z-Buffering and Gouraud Shading
// -----------------------------------------------------------------------------

// Draw line between 2 points, at y position, from left to right.
// Points are start point (On line p1p2) and end point (On line p3p4);
// p1p2 is at the left, p3p4 at the right
static void drawOneGouraudTriangle(SDL_Renderer* renderer,
                                    float *depthBuffer,
                                    int y,
                                    int p1_x, int p1_y, float p1_z,
                                    int p2_x, int p2_y, float p2_z,
                                    int p3_x, int p3_y, float p3_z,
                                    int p4_x, int p4_y, float p4_z,
                                    float cos1, float cos2,
                                    float cos3, float cos4,
                                    int w, int h,
                                    SDL_Color *color) {
    float gradientP1P2 = ((p2_y - p1_y) != 0) ? (y - p1_y) / (float)(p2_y - p1_y) : 1;
    float gradientP3P4 = ((p4_y - p3_y) != 0) ? (y - p3_y) / (float)(p4_y - p3_y) : 1;

    float sx = interpolate(p1_x, p2_x, gradientP1P2);
    float ex = interpolate(p3_x, p4_x, gradientP3P4);

    float z1 = interpolate(p1_z, p2_z, gradientP1P2);
    float z2 = interpolate(p3_z, p4_z, gradientP3P4);

    float c1 = interpolate(cos1, cos2, gradientP1P2);
    float c2 = interpolate(cos3, cos4, gradientP3P4);

    for(int x = sx; x < ex; ++x) {
        // Skip point outside the screen.
        if(x >= 0 && x < w && y >= 0 && y < h) {
            int index = y * w + x;
            float gradientx = (x - sx) / (float)(ex - sx);
            float z = interpolate(z1, z2, gradientx);
            if(depthBuffer[index] > z) {
                depthBuffer[index] = z;
                float c = interpolate(c1, c2, gradientx);
                SDL_SetRenderDrawColor(renderer, color->r * c, color->g * c, color->b * c, color->a);
                SDL_RenderDrawPoint(renderer, x, y);
            }
        }
    }
}

void DrawSDLUtils::drawGouraudTriangle(SDL_Renderer* renderer,
                                        float *depthBuffer,
                                        VertexData & v1,
                                        VertexData & v2,
                                        VertexData & v3,
                                        int w, int h,
                                        SDL_Color *color) {
    // After that, P1 has lower y value and P3 has higher y value.
    if(v1.screenPos->y > v2.screenPos->y) {
        swapVerticeData(v1, v2);
    }
    if(v2.screenPos->y > v3.screenPos->y) {
        swapVerticeData(v2, v3);
    }
    if(v1.screenPos->y > v2.screenPos->y) {
        swapVerticeData(v1, v2);
    }

    const float invSlopeP1P2 = (v2.screenPos->x - v1.screenPos->x) / (float)(v2.screenPos->y - v1.screenPos->y);
    const float invSlopeP1P3 = (v3.screenPos->x - v1.screenPos->x) / (float)(v3.screenPos->y - v1.screenPos->y);

    const VectF3 lightSource(100, 50, -50); // TODO Hard coded, should be moved outside
    const float cos1 = calCosNormLight(*v1.transPos, *v1.normal, lightSource);
    const float cos2 = calCosNormLight(*v2.transPos, *v2.normal, lightSource);
    const float cos3 = calCosNormLight(*v3.transPos, *v3.normal, lightSource);

    // P2 at the right of P1P3
    if(invSlopeP1P2 > invSlopeP1P3) {
        for(int y = v1.screenPos->y; y < v2.screenPos->y; y++) {
            drawOneGouraudTriangle(renderer, depthBuffer, y,
                    v1.screenPos->x, v1.screenPos->y, v1.screenPos->z,
                    v3.screenPos->x, v3.screenPos->y, v3.screenPos->z,
                    v1.screenPos->x, v1.screenPos->y, v1.screenPos->z,
                    v2.screenPos->x, v2.screenPos->y, v2.screenPos->z,
                    cos1, cos3, cos1, cos2,
                    w, h, color);
        }
        for(int y = v2.screenPos->y; y <= v3.screenPos->y; y++) {
            drawOneGouraudTriangle(renderer, depthBuffer, y,
                    v1.screenPos->x, v1.screenPos->y, v1.screenPos->z,
                    v3.screenPos->x, v3.screenPos->y, v3.screenPos->z,
                    v2.screenPos->x, v2.screenPos->y, v2.screenPos->z,
                    v3.screenPos->x, v3.screenPos->y, v3.screenPos->z,
                    cos1, cos3, cos2, cos3,
                    w, h, color);
        }
    }
    // P2 at the left of P1P3
    else {
        for(int y = v1.screenPos->y; y < v2.screenPos->y; y++) {
            drawOneGouraudTriangle(renderer, depthBuffer, y,
                    v1.screenPos->x, v1.screenPos->y, v1.screenPos->z,
                    v2.screenPos->x, v2.screenPos->y, v2.screenPos->z,
                    v1.screenPos->x, v1.screenPos->y, v1.screenPos->z,
                    v3.screenPos->x, v3.screenPos->y, v3.screenPos->z,
                    cos1, cos2, cos1, cos3,
                    w, h, color);
        }
        for(int y = v2.screenPos->y; y <= v3.screenPos->y; y++) {
            drawOneGouraudTriangle(renderer, depthBuffer, y,
                    v2.screenPos->x, v2.screenPos->y, v2.screenPos->z,
                    v3.screenPos->x, v3.screenPos->y, v3.screenPos->z,
                    v1.screenPos->x, v1.screenPos->y, v1.screenPos->z,
                    v3.screenPos->x, v3.screenPos->y, v3.screenPos->z,
                    cos2, cos3, cos1, cos3,
                    w, h, color);
        }
    }
}
