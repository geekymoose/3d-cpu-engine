
#ifndef ENGINE_MATH_MATRIXF4_H_
#define ENGINE_MATH_MATRIXF4_H_

#include "core/config.h"
#include "core/debug.h"
#include "math/VectF4.h"


/**
 * A 4x4 matrix with float components.
 * Use Row vector representation for multiplication and data layout.
 *
 * \since:  Jun 24, 2017
 * \author: Constantin Masson
 */
class MatrixF4 {
    public:
        //Matrix entires indexed by [row][column]
        float m[4][4];

    public:
        MatrixF4();
        explicit MatrixF4(VectF4 const r1, VectF4 const r2, VectF4 const r3, VectF4 const r4);

    public:
        // ---------------------------------------------------------------------
        // General functions
        // ---------------------------------------------------------------------

        /**
         * Returns the transposition matrix of this matrix
         *
         * \return New Transposition matrix
         */
        MatrixF4 transposition() const;


    public:
        // ---------------------------------------------------------------------
        // Static functions
        // ---------------------------------------------------------------------


    public:
        // ---------------------------------------------------------------------
        // Operators overload
        // ---------------------------------------------------------------------

        /**
         * Multiply the matrix by another matrix.
         *
         * \param m Matrix to multiply with
         * \return New matrix resulting from (this * m)
         */
        MatrixF4 operator*(MatrixF4 const& m) const;

        /**
         * Multiply matrix by a scalar.
         * (Each component is multiplied by s)
         *
         * \param s Scalar
         * \return New matrix multiplied by the scalar s.
         */
        MatrixF4 operator*(float const s) const;
} GCC_ALIGNED(16);


// INLINES

// ----------------------------------------------------------------------------
// Constructors - Initialization
// ----------------------------------------------------------------------------
FORCE_INLINE MatrixF4::MatrixF4() {
    m[0][0] = m[0][1] = m[0][2] = m[0][3] = 0.0f;
    m[1][0] = m[1][1] = m[1][2] = m[1][3] = 0.0f;
    m[2][0] = m[2][1] = m[2][2] = m[2][3] = 0.0f;
    m[3][0] = m[3][1] = m[3][2] = m[3][3] = 0.0f;
}

FORCE_INLINE MatrixF4::MatrixF4(VectF4 const v1, VectF4 const v2, VectF4 const v3, VectF4 const v4) {
    m[0][0] = v1.x;  m[0][1] = v1.y;  m[0][2] = v1.z;  m[0][3] = v1.w;
    m[1][0] = v2.x;  m[1][1] = v2.y;  m[1][2] = v2.z;  m[1][3] = v2.w;
    m[2][0] = v3.x;  m[2][1] = v3.y;  m[2][2] = v3.z;  m[2][3] = v3.w;
    m[3][0] = v4.x;  m[3][1] = v4.y;  m[3][2] = v4.z;  m[3][3] = v4.w;
}


// ----------------------------------------------------------------------------
// Operators overload
// ----------------------------------------------------------------------------
FORCE_INLINE MatrixF4 MatrixF4::operator*(MatrixF4 const& o) const {
    VectF4 row1;
    row1.x = m[0][0]*o.m[0][0] + m[0][1]*o.m[1][0] + m[0][2]*o.m[2][0] + m[0][3]*o.m[3][0];
    row1.y = m[0][0]*o.m[0][1] + m[0][1]*o.m[1][1] + m[0][2]*o.m[2][1] + m[0][3]*o.m[3][1];
    row1.z = m[0][0]*o.m[0][2] + m[0][1]*o.m[1][2] + m[0][2]*o.m[2][2] + m[0][3]*o.m[3][2];
    row1.w = m[0][0]*o.m[0][3] + m[0][1]*o.m[1][3] + m[0][2]*o.m[2][3] + m[0][3]*o.m[3][3];
    VectF4 row2;
    row2.x = m[1][0]*o.m[0][0] + m[1][1]*o.m[1][0] + m[1][2]*o.m[2][0] + m[1][3]*o.m[3][0];
    row2.y = m[1][0]*o.m[0][1] + m[1][1]*o.m[1][1] + m[1][2]*o.m[2][1] + m[1][3]*o.m[3][1];
    row2.z = m[1][0]*o.m[0][2] + m[1][1]*o.m[1][2] + m[1][2]*o.m[2][2] + m[1][3]*o.m[3][2];
    row2.w = m[1][0]*o.m[0][3] + m[1][1]*o.m[1][3] + m[1][2]*o.m[2][3] + m[1][3]*o.m[3][3];
    VectF4 row3;
    row2.x = m[2][0]*o.m[0][0] + m[2][1]*o.m[1][0] + m[2][2]*o.m[2][0] + m[2][3]*o.m[3][0];
    row2.y = m[2][0]*o.m[0][1] + m[2][1]*o.m[1][1] + m[2][2]*o.m[2][1] + m[2][3]*o.m[3][1];
    row2.z = m[2][0]*o.m[0][2] + m[2][1]*o.m[1][2] + m[2][2]*o.m[2][2] + m[2][3]*o.m[3][2];
    row2.w = m[2][0]*o.m[0][3] + m[2][1]*o.m[1][3] + m[2][2]*o.m[2][3] + m[2][3]*o.m[3][3];
    VectF4 row4;
    row2.x = m[3][0]*o.m[0][0] + m[3][1]*o.m[1][0] + m[3][2]*o.m[2][0] + m[3][3]*o.m[3][0];
    row2.y = m[3][0]*o.m[0][1] + m[3][1]*o.m[1][1] + m[3][2]*o.m[2][1] + m[3][3]*o.m[3][1];
    row2.z = m[3][0]*o.m[0][2] + m[3][1]*o.m[1][2] + m[3][2]*o.m[2][2] + m[3][3]*o.m[3][2];
    row2.w = m[3][0]*o.m[0][3] + m[3][1]*o.m[1][3] + m[3][2]*o.m[2][3] + m[3][3]*o.m[3][3];
    return MatrixF4(row1, row2, row3, row4);
}

FORCE_INLINE MatrixF4 MatrixF4::operator*(float const s) const {
    return MatrixF4(
            VectF4(m[0][0] * s, m[0][1] * s, m[0][2] * s, m[0][3] * s),
            VectF4(m[1][0] * s, m[1][1] * s, m[1][2] * s, m[1][3] * s),
            VectF4(m[2][0] * s, m[2][1] * s, m[2][2] * s, m[2][3] * s),
            VectF4(m[3][0] * s, m[3][1] * s, m[3][2] * s, m[3][3] * s)
        );
}



#endif // End Header


