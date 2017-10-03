#pragma once

#include <vector>
#include <string>

#include "math/VectF3.h"


// A face is a simple 3D triangle that constitutes a mesh.
typedef struct {
    int a;
    int b;
    int c;
} Face;

/**
 * Mesh is used to represent a 3D object.
 * It is made of a set of vertices.
 *
 * \since   July 2017
 * \author  Constantin Masson
 */
class Mesh {
    public:
        /** The nice mesh's name */
        std::string name;

        /** Mesh's position in 3D world space */
        VectF3 position;

        /** Mesh's rotation */
        VectF3 rotation;

        /** Mesh's scale */
        VectF3 scale;

        /** All mesh's vertices */
        std::vector<VectF3> vertices;

        /** All normal vectors for vertices */
        std::vector<VectF3> normals;

        /** All faces */
        std::vector<Face> faces;

    public:
        Mesh();
        explicit Mesh(std::string name);
};

