#ifndef ENGINE_CORE_ENGINE_H_
#define ENGINE_CORE_ENGINE_H_

#include <SDL2/SDL.h>

#include "render/AppWindow.h"
#include "render/SDL2/AppWindowSDL2.h"
#include "core/Camera.h"
#include "core/Mesh.h"
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
 * \remark
 * This class is subject to many change an is currently used to have a first
 * working version.
 */
class Engine {
    private:
        bool isRunning;
        AppWindowSDL2 renderWindow;


    private:
        // These variable are hard coded for now
        // TODO: Later, add meshes manager systems etc
        std::vector<Mesh> listMeshes;
        Camera cctv; // CCTV is watching you!

    public:
        Engine();

    public:
        bool init();
        bool startRendering();
        bool stopRendering();
        void destroy();

    private:
        bool renderOneFrame();
        void renderAll(SDL_Renderer* renderer, Camera camera, std::vector<Mesh> meshes);
        void DrawPoint(SDL_Renderer* renderer, VectF3 const& p, MatrixF4 const& transformMatrix);
        void handleEvent(SDL_Event* sdlevent);
};


#endif // End header



