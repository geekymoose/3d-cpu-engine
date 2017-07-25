#ifndef ENGINE_MATH_MATRIXF3_H_
#define ENGINE_MATH_MATRIXF3_H_

#include "core/config.h"
#include "core/debug.h"
#include "math/VectF3.h"


/**
 * A 3x3 matrix with float components.
 *
 * \remarks
 * Matrix is stored contiguously in memory in a row fashion:
 * each row contains a single vector.
 *
 * \note
 * TODO: currently not used except to create 4x4 matrix from 3x3.
 *
 * \since:  July 24, 2017
 * \author: Constantin Masson
 */
class MatrixF3 {
    public:
        // Matrix indexed by [row][column]
        float _m[3][3]; // TODO See if alignment is needed here (GCC_ALIGN)

        // Identity Matrix
        static const MatrixF3 IDENTITY;

        // Matrix filled with 0
        static const MatrixF3 ZERO;

    public:
        MatrixF3();
        explicit MatrixF3(VectF3 const r1, VectF3 const r2, VectF3 const r3);
        explicit MatrixF3(
            float m00, float m01, float m02,
            float m10, float m11, float m12,
            float m20, float m21, float m22);

    public:
        // ---------------------------------------------------------------------
        // Class functions
        // ---------------------------------------------------------------------
        // TODO
};


#include "MatrixF3.inl"


#endif // End Header



