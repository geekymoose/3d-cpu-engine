#ifndef ENGINE_MATH_MATRIXF4_H_
#define ENGINE_MATH_MATRIXF4_H_

#include "VectF4.h"
#include "core/debug.h"


/**
 * A 4x4 matrix with float components.
 *
 * \since:  Jun 24, 2017
 * \author: Constantin Masson
 */
class MatrixF4 {
    public:
        float data[4][4];

    public:
        MatrixF4();
        MatrixF4(float values[4][4]);

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
        bool operator==(MatrixF4 const& m) const;
        bool operator!=(MatrixF4 const& m) const;

        VectF4 operator*(MatrixF4 const& m) const;

        /**
         * Multiply this matrix with the vector v.
         *
         * \param v Vector to multiply with.
         * \return New Vector 4 calculated from: this * v .
         */
        VectF4 operator*(VectF4 const& v) const;

        /**
         * Multiply matrix by a scalar.
         * (Each component is multiplied by s)
         *
         * \param s Scalar
         * \return New matrix multiplied by the scalar s.
         */
        MatrixF4 operator*(float const& s) const;
} GCC_ALIGNED(16);


// -----------------------------------------------------------------------------
// Operators overload
// -----------------------------------------------------------------------------


#endif


