#include <cstdlib>
#include <iostream>

#include "core/Engine.h"


int main(int argc, char**argv){
    // Currently, do nothing. Just for debug
    std::cout << "*** Main ***" << std::endl;
    Engine engine;
    engine.init();
    engine.startRendering();
    return EXIT_SUCCESS;
}
