#ifndef ENGINE_MATH_MATRIXF4_H_
#define ENGINE_MATH_MATRIXF4_H_

#include "core/config.h"
#include "core/debug.h"
#include "math/VectF4.h"
#include "math/MatrixF3.h"


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
        // ---------------------------------------------------------------------
        // Class members
        // ---------------------------------------------------------------------

        // Matrix indexed by [row][column]
        float _m[4][4] GCC_ALIGNED(16);

        /**
         * Identity matrix.
         * Matrix filled with 1 on its diagonal.
         *
         * \return New identity matrix.
         */
        static MatrixF4 IDENTITY();

        /**
         * Zero matrix.
         * Matrix filled with 0 everywhere!
         *
         * \return New zero matrix.
         */
        static MatrixF4 ZERO();


    public:
        // ---------------------------------------------------------------------
        // Constructors / Initialization
        // ---------------------------------------------------------------------

        /**
         * Create a new 4x4 matrix filled with zero.
         */
        MatrixF4(void);

        /**
         * Create a new 4x4 matrix with all components set to a specific value.
         *
         * \param value Matrix is filled with it.
         */
        explicit MatrixF4(const float value);

        /**
         * Create a new 4x4 matrix from 4 vectors.
         *
         * \param r1 The matrix row 1.
         * \param r2 The matrix row 2.
         * \param r3 The matrix row 3.
         * \param r4 The matrix row 4.
         */
        explicit MatrixF4(VectF4 const& r1, VectF4 const& r2, VectF4 const& r3, VectF4 const& r4);

        /**
         * Create a new 4x4 matrix with each component explicitly set.
         */
        explicit MatrixF4(
            const float m00, const float m01, const float m02, const float m03,
            const float m10, const float m11, const float m12, const float m13,
            const float m20, const float m21, const float m22, const float m23,
            const float m30, const float m31, const float m32, const float m33);

        /**
         * Create a new 4x4 matrix from a 3x3.
         *
         * \remark
         * A 4x4 matrix can be partitioned into 4 components.
         * The upper 3x3 matrix U.
         * The 1x3 translation vector t.
         * The 3x1 vector of 0.
         * And the scalar 1 at the bottom right.
         *
         * \par
         * The given 3x3 is the U matrix.
         * Translation vector is set to 0 and scalar is set to 1.
         *
         * \par
         * This is the case of Column vector convention.
         * \see MatrixF4 documentation for remind about the used Matrix representation.
         *
         */
        explicit MatrixF4(MatrixF3 const& m3);


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



