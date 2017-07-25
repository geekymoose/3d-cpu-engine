#ifndef ENGINE_MATH_MATRIXF4_TRANSFORM_H_
#define ENGINE_MATH_MATRIXF4_TRANSFORM_H_

#include <cmath>
#include "core/config.h"
#include "core/debug.h"
#include "math/MatrixF4.h"
#include "math/VectF4.h"
#include "math/VectF3.h"


// Macro just to avoid to have 'std::' all over the code
#define SINE(angle) std::sin(angle)
#define COSINE(angle) std::cos(angle)

/**
 * Abstract class that define matrix utilities for transformation.
 * Mean to be used for operation like rotation, translation, specially with matrix 4x4).
 *
 * \remark
 * Matrix multiplication use 'Column vector' transformation.
 * Meaning that M1 * M2 * M3 * Vect will be actually (M1 * (M2 * (M3 * Vect))).
 * This change the structure of transform matrix.
 * For instance, translate matrix as tx, ty, and tz in the last column.
 * (In 'Row vector' multiplication, it is on the last row).
 *
 * \see
 * MatrixF4 class for several information (Read class documentation).
 *
 * \author  Constantin Masson
 */
class MatrixTransform {
    public:
        /**
         * Create a translation matrix from the given vector.
         * \see MatrixTransform for more information about internal representation.
         *
         * \param v The translation vector.
         * \return New translation matrix.
         */
        static MatrixF4 creaTranslate(VectF3 const& v);

        /**
         * Create a translation matrix with the given factors.
         * \see MatrixTransform for more information about internal representation.
         *
         * \param tx The x translation value.
         * \param ty The y translation value.
         * \param tz The z translation value.
         * \return New translation matrix.
         */
        static MatrixF4 creaTranslate(const float tx, const float ty, const float tz);

        /**
         * Create a scale matrix from given vector values.
         *
         * \param v The vector with scale values.
         * \return New scale matrix.
         */
        static MatrixF4 creaScale(VectF3 const& v);

        /**
         * Create a scale matrix from given factors.
         *
         * \param sx The x scale factor.
         * \param sy The y scale factor.
         * \param sz The z scale factor.
         * \return New scale matrix.
         */
        static MatrixF4 creaScale(const float sx, const float sy, const float sz);

        /**
         * Create a rotation matrix on the x axe.
         *
         * \param angle The x rotation in radians.
         * \return The new rotation matrix.
         */
        static MatrixF4 creaRotateX(const float angle);

        /**
         * Create a rotation matrix on the y axe.
         *
         * \param angle The y rotation angle in radians.
         * \return The new rotation matrix.
         */
        static MatrixF4 creaRotateY(const float angle);

        /**
         * Create a rotation matrix on the z axe.
         *
         * \param angle The z rotation angle in radians.
         * \return The new rotation matrix.
         */
        static MatrixF4 creaRotateZ(const float angle);

        /**
         * Create a rotation matrix on the 3 axes.
         *
         * \param angle The x rotation angle in radians.
         * \param angle The y rotation angle in radians.
         * \param angle The z rotation angle in radians.
         * \return The new rotation matrix.
         */
        static MatrixF4 creaRotateXYZ(const float rx, const float ry, const float rz);

        /**
         * Create a LookAt matrix.
         * TODO Documentation to add
         */
        static MatrixF4 creaLookAt(VectF3 const& cPos, VectF3 const& cTarget, VectF3 const& Up);
};


#include "MatrixTransform.inl"


#endif // End header guard



