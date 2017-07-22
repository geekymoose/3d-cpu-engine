#ifndef ENGINE_MATH_MATRIXF4_H_
#define ENGINE_MATH_MATRIXF4_H_

#include "core/config.h"
#include "core/debug.h"
#include "math/VectF4.h"


/**
 * A 4x4 matrix with float components.
 *
 * \remarks
 * Matrix multiplication with Vector use a 'Row vector' representation.
 * This means a multiplication with a vector V is done in the right to left order.
 * For instance, M1 * M2 * M3 * Vect will actually calculate M3 * V1 first.
 * This is an illustration of the final calculation: (M1 * (M2 * (M3 * V1) ) )
 *
 * \par
 * Order is important since matrix multiplication is not commutative.
 * Right to left order is the common representation used by OpenGL for instance.
 *
 * \since:  Jun 24, 2017
 * \author: Constantin Masson
 */
class MatrixF4 {
    public:
        // Matrix indexed by [row][column]
        float _m[4][4] GCC_ALIGNED(16);

        static const MatrixF4 IDENTITY;

    public:
        MatrixF4();
        explicit MatrixF4(VectF4 const r1, VectF4 const r2, VectF4 const r3, VectF4 const r4);
        explicit MatrixF4(
            float m00, float m01, float m02, float m03,
            float m10, float m11, float m12, float m13,
            float m20, float m21, float m22, float m23,
            float m30, float m31, float m32, float m33);

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
         * Multiply the matrix with a Vector.
         * Use row vector representation, so multiplication is done in Right to Left order.
         * (See remark for several informations).
         *
         * \param v Vector to multiply with.
         * \return New vector V2 = matrix * v.
         */
        VectF4 operator*(VectF4 const& v) const;

        /**
         * Multiply matrix by a scalar.
         * (Each component is multiplied by s).
         *
         * \param s Scalar.
         * \return New matrix multiplied by the scalar s.
         */
        MatrixF4 operator*(float const s) const;

        /**
         * Test equality of 2 matrix.
         * This test if both matrix contains same values.
         * (This doesn't check matrix are the same memory entity).
         *
         * \param m Matrix to test with.
         * \return True if this == m, otherwise, return false.
         */
        bool operator==(MatrixF4 const& m) const;
};


#include "MatrixF4.inl"


#endif // End Header



