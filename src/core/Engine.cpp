#include "core/Engine.h"


Engine::Engine() : meshManager(MeshManager::getSingleton()), renderWindow() {
    this->isRunning = false;
}

//------------------------------------------------------------------------------
// Body function (Execution)
//------------------------------------------------------------------------------

bool Engine::init(void){
    this->meshManager.startUp();
    //this->meshManager.loadMeshesFromJSON("./resources/meshes/suzanne.babylon");


    // Init the hard coded elements (Camera, meshes).
    Mesh meshCube;

    // Create vertices
    VectF3 p1(-1, 1, 1);
    VectF3 p2(1, 1, 1);
    VectF3 p3(-1, -1, 1);
    VectF3 p4(1, -1, 1);
    VectF3 p5(-1, 1, -1);
    VectF3 p6(1, 1, -1);
    VectF3 p7(1, -1, -1);
    VectF3 p8(-1, -1, -1);
    meshCube.vertices.push_back(p1);
    meshCube.vertices.push_back(p2);
    meshCube.vertices.push_back(p3);
    meshCube.vertices.push_back(p4);
    meshCube.vertices.push_back(p5);
    meshCube.vertices.push_back(p6);
    meshCube.vertices.push_back(p7);
    meshCube.vertices.push_back(p8);

    // Create faces
    Face f1 = {0, 1, 2};
    Face f2 = {1, 2, 3};
    Face f3 = {1, 3, 6};
    Face f4 = {1, 5, 6};
    Face f5 = {0, 1, 4};
    Face f6 = {1, 4, 5};
    Face f7 = {2, 3, 7};
    Face f8 = {3, 6, 7};
    Face f9 = {0, 2, 7};
    Face f10 = {0, 4, 7};
    Face f11 = {4, 5, 6};
    Face f12 = {4, 6, 7};
    meshCube.faces.push_back(f1);
    meshCube.faces.push_back(f2);
    meshCube.faces.push_back(f3);
    meshCube.faces.push_back(f4);
    meshCube.faces.push_back(f5);
    meshCube.faces.push_back(f6);
    meshCube.faces.push_back(f7);
    meshCube.faces.push_back(f8);
    meshCube.faces.push_back(f9);
    meshCube.faces.push_back(f10);
    meshCube.faces.push_back(f11);
    meshCube.faces.push_back(f12);

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
        this->listMeshes[0].rotation.z += 0.0005;
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
        int color = 100;
        for(auto face : m.faces) {
            VectF3 p1 = this->projectPoint(m.vertices[face.a], transformMatrix);
            VectF3 p2 = this->projectPoint(m.vertices[face.b], transformMatrix);
            VectF3 p3 = this->projectPoint(m.vertices[face.c], transformMatrix);
            color = (color+42) % 255;
            SDL_SetRenderDrawColor(renderer, color, color, color, SDL_ALPHA_OPAQUE);
            this->drawFilledTriangle(renderer, p1, p2, p3);
            //SDL_SetRenderDrawColor(renderer, 92, 92, 92, SDL_ALPHA_OPAQUE);
            //this->drawLine(renderer, p1, p2);
            //this->drawLine(renderer, p2, p3);
            //this->drawLine(renderer, p3, p1);
        }
    }
}

inline VectF3 Engine::projectPoint(VectF3 const& p, MatrixF4 const& mTransform) {
    const VectF4 p_prim = mTransform * VectF4(p.x, p.y, p.z, 1.0f);
    float x = p_prim.x / p_prim.w;
    float y = p_prim.y / p_prim.w;
    float z = p_prim.z / p_prim.w;
    return VectF3(x, y, z);
}

inline void Engine::drawPoint(SDL_Renderer* renderer, VectF3 const& p) {
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

inline void Engine::drawLine(SDL_Renderer* renderer, VectF3 const& p1, VectF3 const& p2) {
    const float w = WINDOW_DEFAULT_SIZE_W;
    const float h = WINDOW_DEFAULT_SIZE_H;
    const float x1 = p1.x * w + w / 2.0f;
    const float y1 = p1.y * h + h / 2.0f;
    const float x2 = p2.x * w + w / 2.0f;
    const float y2 = p2.y * h + h / 2.0f;
    DrawSDLUtils::drawLineDDA(renderer, x1, y1, x2, y2, w, h);
}

inline void Engine::drawFilledTriangle(SDL_Renderer* renderer, VectF3 const& p1, VectF3 const& p2, VectF3 const& p3) {
    const float w = WINDOW_DEFAULT_SIZE_W;
    const float h = WINDOW_DEFAULT_SIZE_H;
    const float x1 = p1.x * w + w / 2.0f;
    const float x2 = p2.x * w + w / 2.0f;
    const float x3 = p3.x * w + w / 2.0f;
    const float y1 = p1.y * h + h / 2.0f;
    const float y2 = p2.y * h + h / 2.0f;
    const float y3 = p3.y * h + h / 2.0f;
    //DrawSDLUtils::drawScanLineTriangle(renderer, x1, y1, x2, y2, x3, y3, w, h);
    DrawSDLUtils::drawScanLineTriangle(renderer, this->depthBuffer, x1, y1, p1.z, x2, y2, p2.z, x3, y3, p3.z, w, h);
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



