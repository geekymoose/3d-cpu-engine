#ifndef ENGINE_CORE_MESH_H_
#define ENGINE_CORE_MESH_H_

#include <vector>
#include <string>
#include "math/VectF3.h"


/**
 * Mesh is a set of vertices to be displayed.
 */
class Mesh {
    public:
        std::string name;
        std::vector<float> vertices;
        VectF3 position;
        VectF3 rotation;

    public:
        Mesh(void);
        explicit Mesh(std::string name);
};


#endif // End header



