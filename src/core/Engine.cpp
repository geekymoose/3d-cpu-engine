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

// Do a projection but don't project on screen, stay un frustum
static VectF3 projectPoint(VectF3 const& v, MatrixF4 const& m) {
    VectF4 vec(v.x, v.y, v.z, 1.0f);
    vec = m * vec;
    vec /= vec.w;
    return VectF3(vec.x, vec.y, vec.z);
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
        int c = 100;
        for(auto & face : m.faces) {
            VectF3 p1_proj = MatrixTransform::projectOnScreen(m.vertices[face.a], transformMatrix, w, h);
            VectF3 p2_proj = MatrixTransform::projectOnScreen(m.vertices[face.b], transformMatrix, w, h);
            VectF3 p3_proj = MatrixTransform::projectOnScreen(m.vertices[face.c], transformMatrix, w, h);

            VectF3 p1_norm = projectPoint(m.normals[face.a], transformMatrix);
            VectF3 p2_norm = projectPoint(m.normals[face.b], transformMatrix);
            VectF3 p3_norm = projectPoint(m.normals[face.c], transformMatrix);

            VectF3 p1_world = projectPoint(m.vertices[face.a], transformMatrix);
            VectF3 p2_world = projectPoint(m.vertices[face.b], transformMatrix);
            VectF3 p3_world = projectPoint(m.vertices[face.c], transformMatrix);

            VertexData v1 = {&p1_proj, &p1_norm, &p1_world};
            VertexData v2 = {&p2_proj, &p2_norm, &p2_world};
            VertexData v3 = {&p3_proj, &p3_norm, &p3_world};

            c = (c + 42) % 255; // TODO TMP generated color
            SDL_Color color;
            color.r = c;
            color.g = c;
            color.b = c;
            color.a = SDL_ALPHA_OPAQUE;
            DrawSDLUtils::drawScanLineTriangle(renderer, depthBuffer, v1, v2, v3, w, h, &color);

            /*
            SDL_SetRenderDrawColor(renderer, 92, 92, 92, SDL_ALPHA_OPAQUE);
            DrawSDLUtils::drawLine(renderer, p1_proj, p2_proj, w, h);
            DrawSDLUtils::drawLine(renderer, p2_proj, p3_proj, w, h);
            DrawSDLUtils::drawLine(renderer, p3_proj, p1_proj, w, h);
            */
        }
        // TODO Temporary rotate the first mesh (And actually unique for now)
        // Note: FPS not fixed. Fast computer -> fast rotation (It's just temporary)
        m.rotation.y += 0.0015;
    }
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



