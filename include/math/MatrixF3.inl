// =============================================================================
// INLINE
// Contains matrix function common to all kind of optimization (SSE, FPU etc)
// Author: Constantin Masson
// =============================================================================


// -----------------------------------------------------------------------------
// Special class members
// -----------------------------------------------------------------------------

FORCE_INLINE MatrixF3 MatrixF3::IDENTITY() {
    return MatrixF3(
        1,0,0,
        0,1,0,
        0,0,1);
}

FORCE_INLINE MatrixF3 MatrixF3::ZERO() {
    return MatrixF3(
        0,0,0,
        0,0,0,
        0,0,0);
}


// -----------------------------------------------------------------------------
// Constructors - Initialization
// -----------------------------------------------------------------------------
FORCE_INLINE MatrixF3::MatrixF3() {
    _m[0][0] = _m[0][1] = _m[0][2] = _m[0][3] = 0.0f;
    _m[1][0] = _m[1][1] = _m[1][2] = _m[1][3] = 0.0f;
    _m[2][0] = _m[2][1] = _m[2][2] = _m[2][3] = 0.0f;
    _m[3][0] = _m[3][1] = _m[3][2] = _m[3][3] = 0.0f;
}

FORCE_INLINE MatrixF3::MatrixF3(VectF3 const& row1,
                                VectF3 const& row2,
                                VectF3 const& row3) {
    _m[0][0] = row1.x; _m[0][1] = row1.y; _m[0][2] = row1.z;
    _m[1][0] = row2.x; _m[1][1] = row2.y; _m[1][2] = row2.z;
    _m[2][0] = row3.x; _m[2][1] = row3.y; _m[2][2] = row3.z;
}

FORCE_INLINE MatrixF3::MatrixF3(
        const float m00, const float m01, const float m02,
        const float m10, const float m11, const float m12,
        const float m20, const float m21, const float m22) {
    // Row 1
    this->_m[0][0] = m00;
    this->_m[0][1] = m01;
    this->_m[0][2] = m02;
    // Row 2
    this->_m[1][0] = m10;
    this->_m[1][1] = m11;
    this->_m[1][2] = m12;
    // Row 3
    this->_m[2][0] = m20;
    this->_m[2][1] = m21;
    this->_m[2][2] = m22;
}


// -----------------------------------------------------------------------------
// Add function specific to optimization type
// -----------------------------------------------------------------------------
// TODO (Currently no implementation)
