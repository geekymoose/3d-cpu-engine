#pragma once

#include <cmath>

#include "core/config.h"
#include "core/debug.h"
#include "math/MatrixF3.h"
#include "math/MatrixF4.h"
#include "math/VectF3.h"
#include "math/VectF4.h"


/**
 * Abstract class that defines matrix utilities for transformations.
 * Meant to be used for operation like scaling, rotation, translation, lookAt...
 * (Specially with matrix 4x4).
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
 * For further informations about matrix transformations, some useful links.
 *
 * \see http://www.codinglabs.net/article_world_view_projection_matrix.aspx
 * \see https://web.archive.org/web/20131222170415/http:/robertokoci.com/world-view-projection-matrix-unveiled/
 * \see http://www.opengl-tutorial.org/beginners-tutorials/tutorial-3-matrices/
 * \see http://www.scratchapixel.com/lessons/3d-basic-rendering/perspective-and-orthographic-projection-matrix/building-basic-perspective-projection-matrix
 *
 * \author Constantin Masson
 */
class MatrixTransform {

    private:
        // This is an abstract class
        MatrixTransform() = default;

    // -------------------------------------------------------------------------
    // Translation methods
    // -------------------------------------------------------------------------
    public:

        /**
         * Create a translation matrix from the given vector.
         *
         * \see MatrixTransform
         * For more information about internal representation.
         *
         * \param translate The translation vector.
         * \return New translation matrix.
         */
        static MatrixF4 creaTranslate(VectF3 const& translate);

        /**
         * Create a translation matrix with the given factors.
         *
         * \see MatrixTransform
         * For more information about internal representation.
         *
         * \param translateX The x translation value.
         * \param translateY The y translation value.
         * \param translateZ The z translation value.
         * \return New translation matrix.
         */
        static MatrixF4 creaTranslate(const float translateX,
                                      const float translateY,
                                      const float translateZ);


    // -------------------------------------------------------------------------
    // Scaling methods
    // -------------------------------------------------------------------------
    public:

        /**
         * Create a scale matrix from given vector values.
         *
         * \param scaleXYZ The vector with scale values (tx, ty, tz).
         * \return New scale matrix.
         */
        static MatrixF4 creaScale(VectF3 const& scaleXYZ);

        /**
         * Create a scale matrix from given factors.
         *
         * \param scaleX The x scale factor.
         * \param scaleY The y scale factor.
         * \param scaleZ The z scale factor.
         * \return New scale matrix.
         */
        static MatrixF4 creaScale(const float scaleX,
                                  const float scaleY,
                                  const float scaleZ);


    // -------------------------------------------------------------------------
    // Rotation methods
    // -------------------------------------------------------------------------
    public:

        /**
         * Create a rotation matrix on the x axe.
         *
         * \param radiansX The x rotation in radians.
         * \return The new rotation matrix.
         */
        static MatrixF4 creaRotateX(const float radiansX);

        /**
         * Create a rotation matrix on the y axe.
         *
         * \param radiansY The y rotation angle in radians.
         * \return The new rotation matrix.
         */
        static MatrixF4 creaRotateY(const float radiansY);

        /**
         * Create a rotation matrix on the z axe.
         *
         * \param radiansZ The z rotation angle in radians.
         * \return The new rotation matrix.
         */
        static MatrixF4 creaRotateZ(const float radiansZ);

        /**
         * Create a rotation matrix on the 3 axes.
         * It use the Yaw-Pitch-Roll order.
         *
         * \note
         * To learn more about, search for information about
         * "Converting Euler Angles to a Rotation Matrix".
         *
         * \see http://danceswithcode.net/engineeringnotes/rotations_in_3d/rotations_in_3d_part1.html
         *
         * \param radiansZ The z rotation angle in radians. (Yaw)
         * \param radiansY The y rotation angle in radians. (Pitch)
         * \param radiansX The x rotation angle in radians. (Roll)
         * \return The new rotation matrix.
         */
        static MatrixF4 creaRotateZYX(const float radiansZ,
                                      const float radiansY,
                                      const float radiansX);

        /**
         * Create a rotation matrix on the 3 axes.
         * It use the Yaw-Pitch-Roll order.
         *
         * \param rotateZYX Vector that represents the YawPitchRoll rotation.
         * \return The new rotation matrix.
         */
        static MatrixF4 creaRotateZYX(VectF3 const& rotateZYX);


    // -------------------------------------------------------------------------
    // Matrix Utils methods
    // -------------------------------------------------------------------------
    public:

        /**
         * Create a left-handed (LH) LookAt matrix.
         *
         * \param cameraPos Position of the camera (Eye point).
         * \param targetPos Position of a point camera is pointing toward.
         * \param upVector The up vector for current world. (Generally 0,1,0).
         * \return The left-handed lookAt matrix.
         */
        static MatrixF4 creaLookAtLH(VectF3 const& cameraPos,
                                     VectF3 const& targetPos,
                                     VectF3 const& upVector);

        /**
         * Create a left-handed (LH) perspective projection matrix.
         *
         * The viewed scene is a frustum defined by the Fov angle
         * and the depth distances (Near and far).
         * The field of view (Fov) is the angle the camera see the scene.
         *
         * \param radiansFov Camera scene angle in radians (Must be positive).
         * \param screenWidth Screen width in pixels.
         * \param screenHeight Screen height in pixels.
         * \param near Nearest distance camera can see (Must be positive).
         * \param far Farther distance camera can see (Must be positive).
         * \return The left-handed perspective matrix.
         */
        static MatrixF4 creaPerspectiveFovLH(const float radiansFov,
                                             const float screenWidth,
                                             const float screenHeight,
                                             const float near,
                                             const float far);
        /**
         * Project a 3D point into a 2D screen.
         * Resulting point is a 3D vector (x, y, z) with z is the Z-Buffering.
         *
         * \note
         * The screen use the common upper-left corner as 0:0.
         * Y coordinates are going down.
         *
         * \param point3D The point to project.
         * \param matrixTransform Transformation matrix to apply 
         * \param screenWidth The screen width in pixels.
         * \param screenHeight The screen height in pixels.
         * \return Projected point on the screen.
         */
        static VectF3 projectOnScreen(VectF3 const& point3D,
                                      MatrixF4 const& matrixTransform,
                                      const int screenWidth,
                                      const int screenHeight);
};


#include "MatrixTransform.inl"

