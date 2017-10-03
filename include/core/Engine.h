#pragma once

#include <SDL2/SDL.h>

#include "core/Camera.h"
#include "core/Mesh.h"
#include "core/MeshManager.h"
#include "render/AppWindow.h"
#include "render/SDL2/AppWindowSDL2.h"
#include "render/SDL2/DrawSDLUtils.h"
#include "math/VectF2.h"
#include "math/VectF3.h"
#include "math/VectF4.h"
#include "math/MatrixF3.h"
#include "math/MatrixF4.h"
#include "math/MatrixTransform.h"


// TODO Probably to change later
// Default window value
#define WINDOW_DEFAULT_SIZE_W 960
#define WINDOW_DEFAULT_SIZE_H 540

/**
 * The core engine that runs the rendering.
 *
 * \warning
 * Alpha version subject to many changes.
 */
class Engine {
    private:
        bool isRunning;
        AppWindowSDL2 renderWindow;



    private:
        // These variable are hard coded for now
        Camera cctv; // CCTV is watching you!
        float depthBuffer[WINDOW_DEFAULT_SIZE_W * WINDOW_DEFAULT_SIZE_H];

    public:
        Engine();

    public:
        bool init();
        bool startRendering();
        bool stopRendering();
        void destroy();

    private:
        bool renderOneFrame();
        void renderAll(SDL_Renderer* renderer, Camera camera, std::vector<Mesh> &meshes);
        void handleEvent(SDL_Event* sdlevent);
};

