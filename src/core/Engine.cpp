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
    VectF3 p1(1.0f, -1.0f, -1.0f);
    VectF3 p2(-1.0f, -1.0f, -1.0f);
    VectF3 p3(-1.0f, 1.0f, -1.0f);
    VectF3 p4(1.0f, 1.0f, -1.0f);

    VectF3 p5(1.0f, -1.0f, 1.0f);
    VectF3 p6(-1.0f, -1.0f, 1.0f);
    VectF3 p7(-1.0f, 1.0f, 1.0f);
    VectF3 p8(1.0f, 1.0f, 1.0f);

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
        renderOneFrame();
        while(SDL_PollEvent(&sdlevent)){
            handleEvent(&sdlevent);
        }
    }
    return true;
}

bool Engine::renderOneFrame(){
    SDL_Renderer*   renderer    = this->renderWindow.sdl_renderer;
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
    VectF3 up(0.0f, 1.0f, 0.0f);
    const float fov     = 70.0f; // Just for test, angle is close to 60 degrees.
    const float w       = WINDOW_DEFAULT_SIZE_W;
    const float h       = WINDOW_DEFAULT_SIZE_H;
    viewMatrix          = MatrixTransform::creaLookAtLH(camera.position, camera.target, up);
    projectionMatrix    = MatrixTransform::creaPerspectiveFovLH(fov, w, h, 0.3f, 1.0f);

    // Project each mesh
    for(std::vector<int>::size_type i = 0; i < meshes.size(); i++){
        Mesh &m = meshes[i];
        worldMatrix = MatrixTransform::creaTranslate(m.position) * MatrixTransform::creaRotateZYX(m.rotation);
        MatrixF4 transformMatrix = projectionMatrix * viewMatrix * worldMatrix;
        for(std::vector<int>::size_type j = 0; j < m.vertices.size(); j++){
            this->DrawPoint(renderer, m.vertices[j], transformMatrix);
        }
    }
}

void Engine::DrawPoint(SDL_Renderer* renderer, VectF3 const& p, MatrixF4 const& transformMatrix) {
    VectF4 p2 = transformMatrix * VectF4(p.x, p.y, p.z, 1.0f);
    float x = p2.x / p2.w;
    float y = p2.y / p2.w;
    const float w = WINDOW_DEFAULT_SIZE_W;
    const float h = WINDOW_DEFAULT_SIZE_H;
    x = x * w + w / 2.0f;
    y = y * h + h / 2.0f;
    // TODO Add clipping (Don't draw if point is outside window)
    SDL_RenderDrawPoint(renderer, x, y);
}

bool Engine::stopRendering(){
    this->isRunning = false;
    return true;
}

void Engine::handleEvent(SDL_Event* sdlevent){
    if (sdlevent->type == SDL_QUIT){
        this->stopRendering();
    }
}



