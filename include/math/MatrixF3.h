#pragma once

#include "core/config.h"
#include "core/debug.h"
#include "math/VectF3.h"


/**
 * A 3x3 matrix with floating point precision.
 *
 * \remarks
 * Matrix is stored contiguously in memory in a row fashion:
 * each row contains a single vector.
 *
 * \remarks
 * For further information about matrix representation:
 * \see MatrixF4
 *
 * \note
 * TODO: currently not used except to create 4x4 matrix from 3x3.
 *
 * \since:  July 24, 2017
 * \author: Constantin Masson
 */
class MatrixF3 {
    public:
        // ---------------------------------------------------------------------
        // Class members
        // ---------------------------------------------------------------------

        // Matrix indexed by [row][column]
        float _m[3][3]; // TODO See if alignment is needed here (GCC_ALIGN)

        /**
         * Identity matrix.
         * Matrix filled with 1 on its diagonal.
         *
         * \return New identity matrix.
         */
        static MatrixF3 IDENTITY();

        /**
         * Zero matrix.
         * Matrix filled with 0 everywhere!
         *
         * \return New zero matrix.
         */
        static MatrixF3 ZERO();


    public:
        // ---------------------------------------------------------------------
        // Constructors / Initialization
        // ---------------------------------------------------------------------
        MatrixF3();

        /**
         * Creates a new matrix filled by 3 rows.
         *
         * \param row1 Values for positions m[0][0] to m[0][2].
         * \param row2 Values for positions m[1][0] to m[1][2].
         * \param row3 Values for positions m[2][0] to m[2][2].
         */
        explicit MatrixF3(VectF3 const& row1,
                          VectF3 const& row2,
                          VectF3 const& row3);

        /**
         * Creates a new matrix with each component set respectively.
         *
         * \param m00 Component at Row 0 Column 0.
         * \param m01 Component at Row 0 Column 1.
         * \param m02 Component at Row 0 Column 2.
         *
         * \param m10 Component at Row 1 Column 0.
         * \param m11 Component at Row 1 Column 1.
         * \param m12 Component at Row 1 Column 2.
         *
         * \param m20 Component at Row 2 Column 0.
         * \param m21 Component at Row 2 Column 1.
         * \param m22 Component at Row 2 Column 2.
         */
        explicit MatrixF3(
            const float m00, const float m01, const float m02,
            const float m10, const float m11, const float m12,
            const float m20, const float m21, const float m22);

    public:
        // ---------------------------------------------------------------------
        // Class functions
        // ---------------------------------------------------------------------
        // TODO
};


#include "MatrixF3.inl"

