#include "core/Engine.h"


Engine::Engine() : renderWindow() {
    this->isRunning = false;
}

//------------------------------------------------------------------------------
// Body function (Execution)
//------------------------------------------------------------------------------

bool Engine::init(){
    // Init the hard coded elements (Camera, meshes).
    Mesh meshCube;

    VectF3 p1(-1.f, 1.f, 1.f);
    VectF3 p2(1.f, 1.f, 1.f);
    VectF3 p3(-1.f, -1.f, 1.f);
    VectF3 p4(-1.f, -1.f, -1.f);
    VectF3 p5(-1.f, 1.f, -1.f);
    VectF3 p6(1.f, 1.f, -1.f);
    VectF3 p7(1.f, -1.f, 1.f);
    VectF3 p8(1.f, -1.f, -1.f);

    meshCube.vertices.push_back(p1);
    meshCube.vertices.push_back(p2);
    meshCube.vertices.push_back(p3);
    meshCube.vertices.push_back(p4);

    meshCube.vertices.push_back(p5);
    meshCube.vertices.push_back(p6);
    meshCube.vertices.push_back(p7);
    meshCube.vertices.push_back(p8);

    meshCube.position = VectF3(0.0f);
    meshCube.rotation = VectF3(0.0f);

    this->listMeshes.push_back(meshCube);
    this->cctv.position = VectF3(0.0f, 0.0f, 10.0f);
    this->cctv.target = meshCube.position;

    //Init SDL
    // TODO To export from Engine to a general 'init manager' or something like
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::clog << "[ERR] Unable to init Window. SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    renderWindow.initialize("3D soft Engine", WINDOW_DEFAULT_SIZE_W, WINDOW_DEFAULT_SIZE_H);
    renderWindow.show();
    return true;
}

void destroy(){
    SDL_Quit();
}

bool Engine::startRendering(){
    if(isRunning){
        return false;
    }
    this->isRunning = true;
    // Main loop
    SDL_Event sdlevent;
    while(isRunning){
        /* TODO To update later
        while(SDL_PollEvent(&sdlevent)){
            handleEvent(&sdlevent);
        } */
        SDL_PollEvent(&sdlevent);
        handleEvent(&sdlevent);
        renderOneFrame();

        // TODO Temporary rotate the first mesh (And actually unique for now)
        // Note: FPS not fixed. Fast computer -> fast rotation (It's just temporary)
        this->listMeshes[0].rotation.x += 0.0005;
        this->listMeshes[0].rotation.y += 0.0005;
    }
    return true;
}

bool Engine::renderOneFrame(){
    SDL_Renderer* renderer = this->renderWindow.sdl_renderer;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    this->renderAll(renderer, this->cctv, this->listMeshes);
    SDL_RenderPresent(renderer);
    return true;
}

void Engine::renderAll(SDL_Renderer* renderer, Camera camera, std::vector<Mesh> meshes) {
    // TODO: Dev note: using std::vector is not optimal but working for now
    MatrixF4 viewMatrix;
    MatrixF4 worldMatrix;
    MatrixF4 projectionMatrix;
    const VectF3 up(0.0f, 1.0f, 0.0f);
    const float w       = WINDOW_DEFAULT_SIZE_W;
    const float h       = WINDOW_DEFAULT_SIZE_H;
    viewMatrix          = MatrixTransform::creaLookAtLH(camera.position, camera.target, up);
    projectionMatrix    = MatrixTransform::creaPerspectiveFovLH(1.57f, w, h, 1.0f, 45.0f);

    // Project each mesh
    for(auto m : meshes){
        worldMatrix = MatrixTransform::creaTranslate(m.position) * MatrixTransform::creaRotateZYX(m.rotation);
        MatrixF4 transformMatrix = projectionMatrix * viewMatrix * worldMatrix;
        for(auto vertice : m.vertices) {
            VectF3 projectPoint = this->projectPoint(vertice, transformMatrix);
            this->DrawPoint(renderer, projectPoint);
        }

        // TODO Test draw line -----------------
        VectF3 p1 = this->projectPoint(m.vertices[0], transformMatrix);
        VectF3 p2 = this->projectPoint(m.vertices[1], transformMatrix);
        float x1 = p1.x * w + w / 2.0f;
        float y1 = p1.y * h + h / 2.0f;
        float x2 = p2.x * w + w / 2.0f;
        float y2 = p2.y * h + h / 2.0f;
        SDL_SetRenderDrawColor(renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawPoint(renderer, x2, y2); // Second point
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderDrawPoint(renderer, x1, y1); // First
        DrawSDLUtils::drawLineDDA(renderer, x1, y1, x2, y2, w, h);
        // END DEBUG -----------------
    }
}

VectF3 Engine::projectPoint(VectF3 const& p, MatrixF4 const& mTransform) {
    const VectF4 p_prim = mTransform * VectF4(p.x, p.y, p.z, 1.0f);
    float x = p_prim.x / p_prim.w;
    float y = p_prim.y / p_prim.w;
    float z = p_prim.z / p_prim.w;
    return VectF3(x, y, z);
}

void Engine::DrawPoint(SDL_Renderer* renderer, VectF3 const& p) {
    // TODO replace w and h by actual current size.
    const float w = WINDOW_DEFAULT_SIZE_W;
    const float h = WINDOW_DEFAULT_SIZE_H;
    if(p.z >= 0 && p.z <= 1) {
        if(p.x >= -1 && p.x <= 1 && p.y >= -1 && p.y <= 1) {
            float x = p.x * w + w / 2.0f;
            float y = p.y * h + h / 2.0f;
            SDL_RenderDrawPoint(renderer, x, y);
        }
    }
}

bool Engine::stopRendering(){
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



