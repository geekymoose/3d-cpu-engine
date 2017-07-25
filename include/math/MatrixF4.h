#ifndef ENGINE_MATH_MATRIXF4_H_
#define ENGINE_MATH_MATRIXF4_H_

#include "core/config.h"
#include "core/debug.h"
#include "math/VectF4.h"


/**
 * A 4x4 matrix with float components.
 *
 * \remarks
 * Matrix multiplication with Vector use a 'Column vector' transformation.
 * This means a multiplication with a vector V is done in the right-to-left order.
 * For instance, M1 * M2 * M3 * Vect will actually calculate M3 * V1 first.
 * This is an illustration of the final calculation: (M1 * (M2 * (M3 * V1) ) )
 *
 * \par
 * Order is important since matrix multiplication is not commutative.
 * Right-to-left order is the common representation used by OpenGL for instance.
 *
 * \par
 * Matrix is stored contiguously in memory in a row fashion:
 * each row contains a single vector.
 *
 * \since:  Jun 24, 2017
 * \author: Constantin Masson
 */
class MatrixF4 {
    public:
        // Matrix indexed by [row][column]
        float _m[4][4] GCC_ALIGNED(16);

        // Identity Matrix
        static const MatrixF4 IDENTITY;

        // Matrix filled with 0
        static const MatrixF4 ZERO;

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
        // Class functions
        // ---------------------------------------------------------------------

        /**
         * Returns the transposition of this matrix.
         * Transposition is the matrix where m[i][j] = this[j][i].
         *
         * \return New Transposition matrix.
         */
        MatrixF4 getTransposition() const;

        /**
         * Transpose this matrix in place.
         * Transposition is the matrix where m[i][j] = this[j][i].
         */
        void transpose();


    public:
        // ---------------------------------------------------------------------
        // Getters / Setters
        // ---------------------------------------------------------------------

        /**
         * Set this matrix values from another matrix.
         *
         * \param m The other matrix to copy.
         */
        void set(MatrixF4 const& m);


    public:
        // ---------------------------------------------------------------------
        // Operators overload
        // ---------------------------------------------------------------------

        /**
         * Multiplies this matrix by a scalar and returns the new matrix.
         * Each this component is multiplied by s.
         *
         * \param s Scalar.
         * \return New matrix multiplied by the scalar s.
         */
        MatrixF4 operator*(float const s) const;

        /**
         * Multiplies the matrix with a Vector and returns the new Vector.
         * Use row vector representation, so multiplication is done in Right to Left order.
         * (See remark for several informations).
         *
         * \param v Vector to multiply with.
         * \return New vector V2 = matrix * v.
         */
        VectF4 operator*(VectF4 const& v) const;

        /**
         * Multiplies this matrix with another and returns a new matrix.
         *
         * \param m Matrix to multiply with.
         * \return New matrix resulting from the multiplication (this * m).
         */
        MatrixF4 operator*(MatrixF4 const& m) const;

        /**
         * Multiplies in place this matrix with a scalar.
         *
         * \param s Scalar.
         * \return Reference to this.
         */
        MatrixF4& operator*=(float const s);

        /**
         * Multiplies in place this matrix with another.
         *
         * \param m The other matrix.
         * \return Reference to this.
         */
        MatrixF4& operator*=(MatrixF4 const& m);


        /**
         * Test equality of 2 matrix.
         * This test if both matrix contains same values.
         * (Does not check if matrix are the same memory entity).
         *
         * \param m Matrix to test with.
         * \return True if this == m, otherwise, return false.
         */
        bool operator==(MatrixF4 const& m) const;

        /**
         * Test inequality of 2 matrix.
         * False as soon as at least one value is not equal.
         *
         * \param m Matrix to test with.
         * \return True if this != m, otherwise, return false.
         */
        bool operator!=(MatrixF4 const& m) const;
};


#include "MatrixF4.inl"


#endif // End Header



