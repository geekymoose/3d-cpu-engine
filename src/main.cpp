#include <cstdlib>
#include <iostream>

#include "core/Engine.h"


int main(int argc, char**argv){
    std::cout << "*** Main ***" << std::endl;
    Engine& engine = Engine::getInstance();
    engine.init();
    engine.startRendering();
    return EXIT_SUCCESS;
}
