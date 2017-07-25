// =============================================================================
// INLINE
// Contains matrix function common to all kind of optimization (SSE, FPU etc)
// Author: Constantin Masson
// =============================================================================


// -----------------------------------------------------------------------------
// Constants
// -----------------------------------------------------------------------------
const MatrixF3 MatrixF3::IDENTITY(
        1,0,0,
        0,1,0,
        0,0,1);

const MatrixF3 MatrixF3::ZERO(
        0,0,0,
        0,0,0,
        0,0,0);


// -----------------------------------------------------------------------------
// Constructors - Initialization
// -----------------------------------------------------------------------------
FORCE_INLINE MatrixF3::MatrixF3() {
    _m[0][0] = _m[0][1] = _m[0][2] = _m[0][3] = 0.0f;
    _m[1][0] = _m[1][1] = _m[1][2] = _m[1][3] = 0.0f;
    _m[2][0] = _m[2][1] = _m[2][2] = _m[2][3] = 0.0f;
    _m[3][0] = _m[3][1] = _m[3][2] = _m[3][3] = 0.0f;
}

FORCE_INLINE MatrixF3::MatrixF3(VectF3 const v1, VectF3 const v2, VectF3 const v3) {
    _m[0][0] = v1.x; _m[0][1] = v1.y; _m[0][2] = v1.z;
    _m[1][0] = v2.x; _m[1][1] = v2.y; _m[1][2] = v2.z;
    _m[2][0] = v3.x; _m[2][1] = v3.y; _m[2][2] = v3.z;
}

FORCE_INLINE MatrixF3::MatrixF3(
        float m00, float m01, float m02,
        float m10, float m11, float m12,
        float m20, float m21, float m22) {
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
