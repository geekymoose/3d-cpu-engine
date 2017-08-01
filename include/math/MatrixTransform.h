#ifndef ENGINE_MATH_MATRIX_TRANSFORM_H_
#define ENGINE_MATH_MATRIX_TRANSFORM_H_

#include <cmath>
#include "core/config.h"
#include "core/debug.h"
#include "math/MatrixF3.h"
#include "math/MatrixF4.h"
#include "math/VectF3.h"
#include "math/VectF4.h"


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
 * \remark
 * For further informations about matrix transformations,
 * here some useful links.
 * \see http://www.codinglabs.net/article_world_view_projection_matrix.aspx
 * \see https://web.archive.org/web/20131222170415/http:/robertokoci.com/world-view-projection-matrix-unveiled/
 * \see http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/
 * \see http://www.scratchapixel.com/lessons/3d-basic-rendering/perspective-and-orthographic-projection-matrix/building-basic-perspective-projection-matrix
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
         * It use the Yaw-Pitch-Roll order.
         *
         * \note
         * To learn more about, search for information about
         * "Converting Euler Angles to a Rotation Matrix".
         * \see http://danceswithcode.net/engineeringnotes/rotations_in_3d/rotations_in_3d_part1.html
         * For more informations.
         *
         * \param angle The z rotation angle in radians. (Yaw)
         * \param angle The y rotation angle in radians. (Pitch)
         * \param angle The x rotation angle in radians. (Roll)
         * \return The new rotation matrix.
         */
        static MatrixF4 creaRotateZYX(const float rz, const float ry, const float rx);

        /**
         * Create a LookAt matrix left-handed (LH).
         *
         * \param cPos Position of the camera (Eye point).
         * \param cTarget Position of a point camera is pointing toward.
         * \param cUp The up vector for the current world. (Generally 0,1,0).
         * \return The lookAt matrix.
         */
        static MatrixF4 creaLookAtLH(VectF3 const& cPos, VectF3 const& cTarget, VectF3 const& Up);

        /**
         * Create a left-handed (LH) perspective projection matrix.
         * The viewed scene is a frustum defined by the Fov angle
         * and the depth distances (Near and far).
         * The field of view (Fov) is the angle the camera see the scene.
         *
         * \param fov Field of View. Camera scene angle in radians. (Must be positive).
         * \param h Screen height (Number of pixels).
         * \param w Screen width (Number of pixels).
         * \param n Nearest distance camera can see. (Must be positive)
         * \param f Farther distance camera can see. (Must be positive)
         * \return The left-handed perspective matrix.
         */
        static MatrixF4 creaPerspectiveFovLH(float fov, float w, float h, float n, float f);
};


#include "MatrixTransform.inl"


#endif // End header guard



