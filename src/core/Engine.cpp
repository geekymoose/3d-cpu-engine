#include "core/Engine.h"


Engine::Engine() : meshManager(MeshManager::getSingleton()), renderWindow() {
    this->isRunning = false;
}

//------------------------------------------------------------------------------
// Body function (Execution)
//------------------------------------------------------------------------------

bool Engine::init(void){
    this->meshManager.startUp();
    this->meshManager.loadMeshesFromJSON("resources/meshes/suzanne.babylon");
    this->cctv.position = VectF3(0.0f, 0.0f, -4.0f);
    this->cctv.target = VectF3(0.0f, 0.0f, 0.0f);

    //Init SDL
    // TODO Dev Note: To export from Engine to a general 'init manager' or something like
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::clog << "[ERR] Unable to init Window. SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    renderWindow.initialize("3D soft Engine", WINDOW_DEFAULT_SIZE_W, WINDOW_DEFAULT_SIZE_H);
    renderWindow.show();
    return true;
}

void destroy(void){
    SDL_Quit();
}

bool Engine::startRendering(void){
    if(isRunning){
        return false;
    }
    this->isRunning = true;
    // Main loop
    SDL_Event sdlevent;
    while(isRunning){
        while(SDL_PollEvent(&sdlevent)){
            handleEvent(&sdlevent);
        }
        handleEvent(&sdlevent);
        renderOneFrame();
    }
    return true;
}

bool Engine::renderOneFrame(void){
    for(int k = 0; k < WINDOW_DEFAULT_SIZE_H * WINDOW_DEFAULT_SIZE_W; k++) {
        this->depthBuffer[k] = 2;
    }
    SDL_Renderer* renderer = this->renderWindow.sdl_renderer;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    this->renderAll(renderer, this->cctv, this->meshManager.listMeshes);
    SDL_RenderPresent(renderer);
    return true;
}

void Engine::renderAll(SDL_Renderer* renderer, Camera camera, std::vector<Mesh> &meshes) {
    MatrixF4 viewMatrix;
    MatrixF4 worldMatrix;
    MatrixF4 projectionMatrix;
    const VectF3 up(0.0f, 1.0f, 0.0f);
    const float w       = WINDOW_DEFAULT_SIZE_W;
    const float h       = WINDOW_DEFAULT_SIZE_H;
    viewMatrix          = MatrixTransform::creaLookAtLH(camera.position, camera.target, up);
    projectionMatrix    = MatrixTransform::creaPerspectiveFovLH(1.57f, w, h, 1.0f, 45.0f);

    // Project each mesh
    for(Mesh & m : meshes){
        worldMatrix = MatrixTransform::creaTranslate(m.position) * MatrixTransform::creaRotateZYX(m.rotation);
        MatrixF4 transformMatrix = projectionMatrix * viewMatrix * worldMatrix;
        int color = 100;
        for(auto & face : m.faces) {
            VectF3 p1 = this->projectPoint(m.vertices[face.a], transformMatrix);
            VectF3 p2 = this->projectPoint(m.vertices[face.b], transformMatrix);
            VectF3 p3 = this->projectPoint(m.vertices[face.c], transformMatrix);
            color = (color+42) % 255;
            SDL_SetRenderDrawColor(renderer, color, color, color, SDL_ALPHA_OPAQUE);
            DrawSDLUtils::drawFilledTriangle(renderer, this->depthBuffer, p1, p2, p3, w, h);

            /*
            SDL_SetRenderDrawColor(renderer, 92, 92, 92, SDL_ALPHA_OPAQUE);
            DrawSDLUtils::drawLine(renderer, p1, p2, w, h);
            DrawSDLUtils::drawLine(renderer, p2, p3, w, h);
            DrawSDLUtils::drawLine(renderer, p3, p1, w, h);
            */
        }
        // TODO Temporary rotate the first mesh (And actually unique for now)
        // Note: FPS not fixed. Fast computer -> fast rotation (It's just temporary)
        m.rotation.y += 0.0005;
    }
}

inline VectF3 Engine::projectPoint(VectF3 const& p, MatrixF4 const& mTransform) {
    const VectF4 p_prim = mTransform * VectF4(p.x, p.y, p.z, 1.0f);
    float x = p_prim.x  / p_prim.w;
    float y = p_prim.y  / p_prim.w;
    float z = p_prim.z  / p_prim.w;
    return VectF3(x, y, z);
}

bool Engine::stopRendering(void){
    this->isRunning = false;
    return true;
}

void Engine::handleEvent(SDL_Event* sdlevent){
    switch (sdlevent->type) {
        case SDL_QUIT:
            this->stopRendering();
            break;
        case SDL_MOUSEWHEEL:
            cctv.position.z += sdlevent->wheel.y * 0.005f;
            break;

    }
}



