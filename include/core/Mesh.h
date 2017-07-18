#ifndef ENGINE_CORE_MESH_H_
#define ENGINE_CORE_MESH_H_

#include <vector>
#include <string>
#include "math/VectF3.h"


/**
 * Mesh is used to represent a 3D object.
 * It is made of a set of vertices.
 */
class Mesh {
    public:
        /** The nice mesh's name */
        std::string name;

        /** All mesh's vertices */
        std::vector<VectF3> vertices;

        /** Mesh's position in 3D world space */
        VectF3 position;

        /** Mesh's rotation */
        VectF3 rotation;

    public:
        Mesh(void);
        explicit Mesh(std::string name);
};


#endif // End header



