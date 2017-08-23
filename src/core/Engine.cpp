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
    this->cctv.target = this->meshManager.listMeshes[0].position;

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
    // TODO : DEV NOTE (To update with 'Elasped Time' system)
    // Currently, the game loop is a CPU-Dependent timer, meaning that it will
    // run faster on fast CPUs
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
    MatrixF4 projectionMatrix;
    const VectF3 up(0.0f, 1.0f, 0.0f);
    const float w       = WINDOW_DEFAULT_SIZE_W;
    const float h       = WINDOW_DEFAULT_SIZE_H;
    viewMatrix          = MatrixTransform::creaLookAtLH(camera.position, camera.target, up);
    projectionMatrix    = MatrixTransform::creaPerspectiveFovLH(1.57f, w, h, 1.0f, 45.0f);

    // Project each mesh
    for(Mesh & m : meshes){
        const MatrixF4 posMatrix        = MatrixTransform::creaTranslate(m.position);
        const MatrixF4 rotMatrix        = MatrixTransform::creaRotateZYX(m.rotation);
        const MatrixF4 scaMatrix        = MatrixTransform::creaScale(m.scale);
        const MatrixF4 worldMatrix      = posMatrix * rotMatrix * scaMatrix;
        const MatrixF4 cameraMatrix     = viewMatrix * worldMatrix;
        const MatrixF4 transformMatrix  = projectionMatrix * cameraMatrix;
        for(auto & face : m.faces) {
            // Project 3 vertices in the 2D screen coordinates
            VectF3 p1_proj = MatrixTransform::projectOnScreen(m.vertices[face.a], transformMatrix, w, h);
            VectF3 p2_proj = MatrixTransform::projectOnScreen(m.vertices[face.b], transformMatrix, w, h);
            VectF3 p3_proj = MatrixTransform::projectOnScreen(m.vertices[face.c], transformMatrix, w, h);

            // Project normals in world coordinates
            VectF3 p1_norm = projectPoint(m.normals[face.a], worldMatrix);
            VectF3 p2_norm = projectPoint(m.normals[face.b], worldMatrix);
            VectF3 p3_norm = projectPoint(m.normals[face.c], worldMatrix);

            // Project positions in world coordinates
            VectF3 p1_pos = projectPoint(m.vertices[face.a], worldMatrix);
            VectF3 p2_pos = projectPoint(m.vertices[face.b], worldMatrix);
            VectF3 p3_pos = projectPoint(m.vertices[face.c], worldMatrix);

            VertexData v1 = {&p1_proj, &p1_norm, &p1_pos};
            VertexData v2 = {&p2_proj, &p2_norm, &p2_pos};
            VertexData v3 = {&p3_proj, &p3_norm, &p3_pos};

            // Color of the light (To refactor)
            SDL_Color color;
            color.r = 255;
            color.g = 240;
            color.b = 42;
            color.a = SDL_ALPHA_OPAQUE;
            DrawSDLUtils::drawScanLineTriangle(renderer, depthBuffer, v1, v2, v3, w, h, &color);
            /*
            SDL_SetRenderDrawColor(renderer, 92, 92, 92, SDL_ALPHA_OPAQUE);
            DrawSDLUtils::drawLine(renderer, p1_proj, p2_proj, w, h);
            DrawSDLUtils::drawLine(renderer, p2_proj, p3_proj, w, h);
            DrawSDLUtils::drawLine(renderer, p3_proj, p1_proj, w, h);
            */
        }
        m.rotation.y += 0.0015; //TODO tmp
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



