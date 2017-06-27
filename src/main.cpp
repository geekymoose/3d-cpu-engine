#include <cstdlib>
#include <iostream>
#include "math/VectF4.h"
#include "math/MatrixF4.h"
#include "core/debug.h"


int main(int argc, char**argv){
    std::cout << "*** Main ***" << std::endl;
    VectF4 v1;
    VectF4 v2(1.0f,2.0f,3.0f,4.0f);
    ASSERT(1==1);
    MatrixF4 m1;
    return EXIT_SUCCESS;
}
