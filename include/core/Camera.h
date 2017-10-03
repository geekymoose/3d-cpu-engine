#pragma once

#include "math/VectF3.h"


/**
 * The main camera component.
 * View point from where there scene is rendered.
 */
class Camera {
    public:
        // Position of the camera in world space.
        VectF3 position;

        // Position of the target in world space (Camera look at target).
        VectF3 target;

    public:
        Camera();
};

