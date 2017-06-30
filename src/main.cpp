#include <cstdlib>
#include <iostream>
#include "math/VectF4.h"
#include "math/MatrixF4.h"
#include "math/VectF3.h"
#include "core/debug.h"
#include "core/Mesh.h"
#include "core/Camera.h"


int main(int argc, char**argv){
    // Currently, do nothing. Just for debug
    std::cout << "*** Main ***" << std::endl;
    VectF4 v1;
    VectF4 v2(1.0f,2.0f,3.0f,4.0f);
    VectF3 v3(1.0f,2.0f,3.0f);
    ASSERT(1==1);
    MatrixF4 m1;
    Camera camera;
    Mesh cube("A Nice Cube");
    return EXIT_SUCCESS;
}
