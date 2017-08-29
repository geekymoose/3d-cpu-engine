// =============================================================================
// INLINE
// General inlined definitions for MatrixTransform.
// Author: Constantin Masson
// =============================================================================


// -----------------------------------------------------------------------------
// Translation methods
// -----------------------------------------------------------------------------

FORCE_INLINE MatrixF4 MatrixTransform::creaTranslate(VectF3 const& translate) {
    return MatrixTransform::creaTranslate(translate.x, translate.y, translate.z);
}

FORCE_INLINE MatrixF4 MatrixTransform::creaTranslate(const float translateX,
                                                     const float translateY,
                                                     const float translateZ) {
    MatrixF4 momo = MatrixF4::IDENTITY(); // Yeah, momo is a cool name
    momo._m[0][3] = translateX;
    momo._m[1][3] = translateY;
    momo._m[2][3] = translateZ;
    return momo; // [3][3] already sets to 1 thanks to IDENTITY
}


// -----------------------------------------------------------------------------
// Scaling methods
// -----------------------------------------------------------------------------

FORCE_INLINE MatrixF4 MatrixTransform::creaScale(VectF3 const& scaleXVZ) {
    return MatrixTransform::creaScale(scaleXVZ.x, scaleXVZ.y, scaleXVZ.z);
}

FORCE_INLINE MatrixF4 MatrixTransform::creaScale(const float scaleX,
                                                 const float scaleY,
                                                 const float scaleZ) {
    MatrixF4 soso = MatrixF4::ZERO();
    soso._m[0][0] = scaleX;
    soso._m[1][1] = scaleY;
    soso._m[2][2] = scaleZ;
    soso._m[3][3] = 1.0f;
    return soso;
}


// -----------------------------------------------------------------------------
// Rotation methods
// -----------------------------------------------------------------------------

FORCE_INLINE MatrixF4 MatrixTransform::creaRotateX(const float radiansX) {
    MatrixF4 roo = MatrixF4::IDENTITY(); // Pronounced "Roooohhh!!!"
    const float cos = std::cos(radiansX);
    const float sin = std::sin(radiansX);
    roo._m[1][1] = cos;
    roo._m[1][2] = -sin;
    roo._m[2][1] = sin;
    roo._m[2][2] = cos;
    return roo;
}

FORCE_INLINE MatrixF4 MatrixTransform::creaRotateY(const float radiansY) {
    MatrixF4 roo = MatrixF4::IDENTITY(); // Pronounced "Roooohhh!!!"
    const float cos = std::cos(radiansY);
    const float sin = std::sin(radiansY);
    roo._m[0][0] = cos;
    roo._m[0][2] = sin;
    roo._m[2][0] = -sin;
    roo._m[2][2] = cos;
    return roo;
}

FORCE_INLINE MatrixF4 MatrixTransform::creaRotateZ(const float radiansZ) {
    MatrixF4 roo = MatrixF4::IDENTITY(); // Pronounced "Roooohhh!!!"
    const float cos = std::cos(radiansZ);
    const float sin = std::sin(radiansZ);
    roo._m[0][0] = cos;
    roo._m[0][1] = -sin;
    roo._m[1][0] = sin;
    roo._m[1][1] = cos;
    return roo;
}

FORCE_INLINE MatrixF4 MatrixTransform::creaRotateZYX(const float radiansZ,
                                                     const float radiansY,
                                                     const float radiansX) {
    MatrixF4 mRotate = MatrixF4::IDENTITY();
    mRotate *= MatrixTransform::creaRotateZ(radiansZ);
    mRotate *= MatrixTransform::creaRotateY(radiansY);
    mRotate *= MatrixTransform::creaRotateX(radiansX);
    return mRotate;
}

FORCE_INLINE MatrixF4 MatrixTransform::creaRotateZYX(VectF3 const& rotateZYX) {
    return MatrixTransform::creaRotateZYX(rotateZYX.x, rotateZYX.y, rotateZYX.z);
}


// -----------------------------------------------------------------------------
// Matrix Utils methods
// -----------------------------------------------------------------------------

FORCE_INLINE MatrixF4 MatrixTransform::creaLookAtLH(VectF3 const& cameraPos,
                                                    VectF3 const& targetPos,
                                                    VectF3 const& upVector) {
    // Creates the 3 Camera's vectors.
    VectF3 cx, cy, cz;
    cz = targetPos - cameraPos;
    cx = VectF3::crossProduct(upVector, cz);
    cy = VectF3::crossProduct(cz, cx);
    cz.normalizeFast();
    cx.normalizeFast();
    cy.normalizeFast();

    // Creates the lookAt matrix from camera vectors.
    MatrixF3 m3(cx, cy, cz);
    MatrixF4 mLookAt(m3);
    mLookAt._m[0][3] = -(VectF3::dotProduct(cx, cameraPos));
    mLookAt._m[1][3] = -(VectF3::dotProduct(cy, cameraPos));
    mLookAt._m[2][3] = -(VectF3::dotProduct(cz, cameraPos));
    return mLookAt;
}

FORCE_INLINE MatrixF4 MatrixTransform::creaPerspectiveFovLH(
        const float radiansFov,
        const float screenWidth,
        const float screenHeight,
        const float near,
        const float far) {
    // TODO Add assert to check invalid values
    MatrixF4 result     = MatrixF4::ZERO();
    const float cotanFov= 1 / std::tan(radiansFov * 0.5);
    const float depth   = far - near;
    const float aspect  = screenHeight / screenWidth;
    // Actual ratio is w/h but x / (w/h) == x * (h/w)
    result._m[0][0]     = cotanFov * aspect;
    result._m[1][1]     = cotanFov;
    result._m[2][2]     = far / depth;
    result._m[2][3]     = -(far * near) / depth;
    result._m[3][2]     = 1.0f;
    return result;
}

FORCE_INLINE VectF3 MatrixTransform::projectOnScreen(
        VectF3 const& point3D,
        MatrixF4 const& matrixTransform,
        const int screenWidth,
        const int screenHeight) {
    VectF4 vec  = VectF4(point3D.x, point3D.y, point3D.z, 1.0f);
    vec         = matrixTransform * vec;
    vec         /= vec.w;
    vec.x       = (vec.x * screenWidth) + (screenWidth * 0.5);
    vec.y       = (-vec.y * screenHeight) + (screenHeight * 0.5);
    // upper-left is 0:0 thuz -vec.y
    return VectF3(vec.x, vec.y, vec.z);
}
