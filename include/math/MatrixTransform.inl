// =============================================================================
// INLINE
// General inlined definitions for MatrixTransform.
// Author: Constantin Masson
// =============================================================================


FORCE_INLINE MatrixF4 MatrixTransform::creaTranslate(VectF3 const& v) {
    return MatrixTransform::creaTranslate(v.x, v.y, v.z);
}

FORCE_INLINE MatrixF4 MatrixTransform::creaTranslate(const float tx, const float ty, const float tz) {
    MatrixF4 momo = MatrixF4::IDENTITY(); // Yeah, momo is a cool name
    momo._m[0][3] = tx;
    momo._m[1][3] = ty;
    momo._m[2][3] = tz;
    return momo; // In case of: [3][3] already set to 1 thanks to IDENTITY
}

FORCE_INLINE MatrixF4 MatrixTransform::creaScale(VectF3 const& v) {
    return MatrixTransform::creaScale(v.x, v.y, v.z);
}

FORCE_INLINE MatrixF4 MatrixTransform::creaScale(const float sx, const float sy, const float sz) {
    MatrixF4 soso = MatrixF4::ZERO();
    soso._m[0][0] = sx;
    soso._m[1][1] = sy;
    soso._m[2][2] = sz;
    soso._m[3][3] = 1;
    return soso;
}

FORCE_INLINE MatrixF4 MatrixTransform::creaRotateX(const float angle) {
    MatrixF4 roo = MatrixF4::IDENTITY(); // Pronounce "Roooohhh!!!" like if someone does something stupid! :P
    const float c = std::cos(angle);
    const float s = std::sin(angle);
    roo._m[1][1] = c;
    roo._m[1][2] = -s;
    roo._m[2][1] = s;
    roo._m[2][2] = c;
    return roo;
}

FORCE_INLINE MatrixF4 MatrixTransform::creaRotateY(const float angle) {
    MatrixF4 roo = MatrixF4::IDENTITY();
    const float c = std::cos(angle);
    const float s = std::sin(angle);
    roo._m[0][0] = c;
    roo._m[0][2] = s;
    roo._m[2][0] = -s;
    roo._m[2][2] = c;
    return roo;
}

FORCE_INLINE MatrixF4 MatrixTransform::creaRotateZ(const float angle) {
    MatrixF4 roo = MatrixF4::IDENTITY();
    const float c = std::cos(angle);
    const float s = std::sin(angle);
    roo._m[0][0] = c;
    roo._m[0][1] = -s;
    roo._m[1][0] = s;
    roo._m[1][1] = c;
    return roo;
}

FORCE_INLINE MatrixF4 MatrixTransform::creaRotateZYX(const float rz, const float ry, const float rx) {
    MatrixF4 m = MatrixF4::IDENTITY();
    m *= MatrixTransform::creaRotateZ(rz);
    m *= MatrixTransform::creaRotateY(ry);
    m *= MatrixTransform::creaRotateX(rx);
    return m;
}

FORCE_INLINE MatrixF4 MatrixTransform::creaRotateZYX(VectF3 const& v) {
    return MatrixTransform::creaRotateZYX(v.x, v.y, v.z);
}

FORCE_INLINE MatrixF4 MatrixTransform::creaLookAtLH(VectF3 const& cPos, VectF3 const& cTarget, VectF3 const& cUp) {
    // Creates the 3 Camera's vectors.
    VectF3 cx, cy, cz;
    cz = cTarget - cPos;
    cx = VectF3::crossProduct(cUp, cz);
    cy = VectF3::crossProduct(cz, cx);
    cz.normalizeFast();
    cx.normalizeFast();
    cy.normalizeFast();

    // Creates the lookAt matrix from camera vectors.
    MatrixF3 m3(cx, cy, cz);
    MatrixF4 m(m3);
    m._m[0][3] = -(VectF3::dotProduct(cx, cPos));
    m._m[1][3] = -(VectF3::dotProduct(cy, cPos));
    m._m[2][3] = -(VectF3::dotProduct(cz, cPos));
    return m;
}

FORCE_INLINE MatrixF4 MatrixTransform::creaPerspectiveFovLH(float fov, float w, float h, float n, float f) {
    // TODO Add assert to check invalid values
    MatrixF4 result     = MatrixF4::ZERO();
    const float cotanFov= 1 / std::tan(fov * 0.5);
    const float depth   = f - n;
    const float aspect  = h / w; // Actual ratio is w/h but x/(w/h) == x*(h/w)
    result._m[0][0]     = cotanFov * aspect;
    result._m[1][1]     = cotanFov;
    result._m[2][2]     = f / depth;
    result._m[2][3]     = -(f * n) / depth;
    result._m[3][2]     = 1.0f;
    return result;
}

FORCE_INLINE VectF3 MatrixTransform::projectOnScreen(VectF3 const& point,
                                                     MatrixF4 const& mTransform,
                                                     const int width,
                                                     const int height) {
    VectF4 vec = VectF4(point.x, point.y, point.z, 1.0f);
    vec = mTransform * vec;
    vec /= vec.w;
    vec.x = (vec.x * width) + (width * 0.5);
    vec.y = (-vec.y * height) + (height * 0.5); // upper-left is 0:0 thuz -y
    return VectF3(vec.x, vec.y, vec.z);
}
