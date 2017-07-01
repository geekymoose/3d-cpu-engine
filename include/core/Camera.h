#ifndef ENGINE_CORE_CAMERA_H_
#define ENGINE_CORE_CAMERA_H_

#include "math/VectF3.h"


/**
 * The main camera component.
 * View point from where there scene is rendered.
 */
class Camera {
    public:
        VectF3 position;
        VectF3 target;

    public:
        Camera(void);
};


#endif // End header



