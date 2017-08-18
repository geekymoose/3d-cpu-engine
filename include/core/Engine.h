#ifndef ENGINE_CORE_ENGINE_H_
#define ENGINE_CORE_ENGINE_H_

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
 * \remark
 * This class is subject to many change an is currently used to have a first
 * working version.
 * Don't pay attention to ugly elements that will go away later.
 */
class Engine {
    private:
        MeshManager &meshManager;

    private:
        bool isRunning;
        AppWindowSDL2 renderWindow;

        float depthBuffer[WINDOW_DEFAULT_SIZE_W * WINDOW_DEFAULT_SIZE_H]; // TODO tmp


    private:
        // These variable are hard coded for now
        //std::vector<Mesh> listMeshes;
        Camera cctv; // CCTV is watching you!

    public:
        Engine(void);

    public:
        bool init(void);
        bool startRendering(void);
        bool stopRendering(void);
        void destroy(void);

    private:
        bool renderOneFrame(void);
        void renderAll(SDL_Renderer* renderer, Camera camera, std::vector<Mesh> &meshes);
        VectF3 projectPoint(VectF3 const& p, MatrixF4 const& mTransform);
        void handleEvent(SDL_Event* sdlevent);
};


#endif // End header



