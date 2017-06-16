#include <cstdlib>
#include <iostream>
#include "math/VectF4.h"


// Tmp debug function
void dbg_vect(VectF4 const& v){
    std::cout << "*** Debug Vector Data: " << std::endl;
    std::cout << " - Pos: " << v << std::endl;
    std::cout << " - Len: " << v.length() << std::endl;
}

int main(int argc, char**argv){
    std::cout << "*** Main ***" << std::endl;
    VectF4 v1;
    dbg_vect(v1);

    VectF4 v2(1.0f,2.0f,3.0f,4.0f);
    v2 = v2.normalize();
    dbg_vect(v2);

    return EXIT_SUCCESS;
}
