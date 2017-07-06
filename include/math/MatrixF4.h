#ifndef ENGINE_MATH_MATRIXF4_H_
#define ENGINE_MATH_MATRIXF4_H_

#include "core/config.h"
#include "core/debug.h"
#include "math/VectF4.h"


/**
 * A 4x4 matrix with float components.
 * Use Row vector representation for multiplication and data layout.
 * Multiplication is done in a left to right order.
 * Meaning that M1 * M2 * M3 , multiplication order is 1, 2, then 3.
 *
 * \since:  Jun 24, 2017
 * \author: Constantin Masson
 */
class MatrixF4 {
    public:
        //Matrix indexed by [row][column]
        float m[4][4];

    public:
        MatrixF4();
        explicit MatrixF4(VectF4 const r1, VectF4 const r2, VectF4 const r3, VectF4 const r4);

    public:
        // ---------------------------------------------------------------------
        // General functions
        // ---------------------------------------------------------------------

        /**
         * Returns the transposition of this matrix.
         *
         * \return New Transposition matrix.
         */
        MatrixF4 transposition() const;


    public:
        // ---------------------------------------------------------------------
        // Operators overload
        // ---------------------------------------------------------------------

        /**
         * Multiply the matrix by another matrix.
         *
         * \param m Matrix to multiply with.
         * \return New matrix resulting from (this * m).
         */
        MatrixF4 operator*(MatrixF4 const& m) const;

        /**
         * Multiply matrix by a scalar.
         * (Each component is multiplied by s).
         *
         * \param s Scalar
         * \return New matrix multiplied by the scalar s.
         */
        MatrixF4 operator*(float const s) const;
} GCC_ALIGNED(16);


#include "MatrixF4.inl"


#endif // End Header



