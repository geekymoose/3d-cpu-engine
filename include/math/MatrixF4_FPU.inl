// =============================================================================
// INLINE MATRIX
// Contains FPU implementation of matrix functions.
// Author: Constantin Masson
//
// TODO: refactoring
// There are probably several duplicates and not optimized thing in term of code size.
// It's ok for now, but refactoring may be a good idea later.
// =============================================================================


// -----------------------------------------------------------------------------
// Constructors - Initialization
// -----------------------------------------------------------------------------
FORCE_INLINE MatrixF4::MatrixF4() {
    _m[0][0] = _m[0][1] = _m[0][2] = _m[0][3] = 0.0f;
    _m[1][0] = _m[1][1] = _m[1][2] = _m[1][3] = 0.0f;
    _m[2][0] = _m[2][1] = _m[2][2] = _m[2][3] = 0.0f;
    _m[3][0] = _m[3][1] = _m[3][2] = _m[3][3] = 0.0f;
}

FORCE_INLINE MatrixF4::MatrixF4(VectF4 const v1, VectF4 const v2, VectF4 const v3, VectF4 const v4) {
    _m[0][0] = v1.x; _m[0][1] = v1.y; _m[0][2] = v1.z; _m[0][3] = v1.w;
    _m[1][0] = v2.x; _m[1][1] = v2.y; _m[1][2] = v2.z; _m[1][3] = v2.w;
    _m[2][0] = v3.x; _m[2][1] = v3.y; _m[2][2] = v3.z; _m[2][3] = v3.w;
    _m[3][0] = v4.x; _m[3][1] = v4.y; _m[3][2] = v4.z; _m[3][3] = v4.w;
}

FORCE_INLINE MatrixF4::MatrixF4(
        float m00, float m01, float m02, float m03,
        float m10, float m11, float m12, float m13,
        float m20, float m21, float m22, float m23,
        float m30, float m31, float m32, float m33) {
    // Row 1
    this->_m[0][0] = m00;
    this->_m[0][1] = m01;
    this->_m[0][2] = m02;
    this->_m[0][3] = m03;
    // Row 2
    this->_m[1][0] = m10;
    this->_m[1][1] = m11;
    this->_m[1][2] = m12;
    this->_m[1][3] = m13;
    // Row 3
    this->_m[2][0] = m20;
    this->_m[2][1] = m21;
    this->_m[2][2] = m22;
    this->_m[2][3] = m23;
    // Row 4
    this->_m[3][0] = m30;
    this->_m[3][1] = m31;
    this->_m[3][2] = m32;
    this->_m[3][3] = m33;
}


// -----------------------------------------------------------------------------
// class functions
// -----------------------------------------------------------------------------
MatrixF4 MatrixF4::getTransposition() const {
    MatrixF4 nMatrix;
    // TODO Note: I have to check, but compiler might optimize this to remove loop
    for(int i=0; i<4; i++) {
        for(int j=0; j<4; j++) {
            nMatrix._m[i][j] = _m[j][i];
        }
    }
    return nMatrix;
}

void MatrixF4::transpose() {
    MatrixF4 m = this->getTransposition();
    this->set(m);
}


// -----------------------------------------------------------------------------
// Operators overload (General)
// -----------------------------------------------------------------------------
FORCE_INLINE MatrixF4 MatrixF4::operator*(float const s) const {
    MatrixF4 nMatrix;
    // Row 1
    nMatrix._m[0][0] = _m[0][0] * s;
    nMatrix._m[0][1] = _m[0][1] * s;
    nMatrix._m[0][2] = _m[0][2] * s;
    nMatrix._m[0][3] = _m[0][3] * s;
    // Row 2
    nMatrix._m[1][0] = _m[1][0] * s;
    nMatrix._m[1][1] = _m[1][1] * s;
    nMatrix._m[1][2] = _m[1][2] * s;
    nMatrix._m[1][3] = _m[1][3] * s;
    // Row 3
    nMatrix._m[2][0] = _m[2][0] * s;
    nMatrix._m[2][1] = _m[2][1] * s;
    nMatrix._m[2][2] = _m[2][2] * s;
    nMatrix._m[2][3] = _m[2][3] * s;
    // Row 4
    nMatrix._m[3][0] = _m[3][0] * s;
    nMatrix._m[3][1] = _m[3][1] * s;
    nMatrix._m[3][2] = _m[3][2] * s;
    nMatrix._m[3][3] = _m[3][3] * s;
    return nMatrix;
}

FORCE_INLINE VectF4 MatrixF4::operator*(VectF4 const& v) const {
    VectF4 nVect;
    nVect.x = _m[0][0] * v.x + _m[0][1] * v.y + _m[0][2] * v.z + _m[0][3] * v.w;
    nVect.y = _m[1][0] * v.x + _m[1][1] * v.y + _m[1][2] * v.z + _m[1][3] * v.w;
    nVect.z = _m[2][0] * v.x + _m[2][1] * v.y + _m[2][2] * v.z + _m[2][3] * v.w;
    nVect.w = _m[3][0] * v.x + _m[3][1] * v.y + _m[3][2] * v.z + _m[3][3] * v.w;
    return nVect;
}

FORCE_INLINE MatrixF4 MatrixF4::operator*(MatrixF4 const& o) const {
    MatrixF4 nMatrix;
    // Row 1
    nMatrix._m[0][0] = _m[0][0] * o._m[0][0] + _m[0][1] * o._m[1][0] + _m[0][2] * o._m[2][0] + _m[0][3] * o._m[3][0];
    nMatrix._m[0][1] = _m[0][0] * o._m[0][1] + _m[0][1] * o._m[1][1] + _m[0][2] * o._m[2][1] + _m[0][3] * o._m[3][1];
    nMatrix._m[0][2] = _m[0][0] * o._m[0][2] + _m[0][1] * o._m[1][2] + _m[0][2] * o._m[2][2] + _m[0][3] * o._m[3][2];
    nMatrix._m[0][3] = _m[0][0] * o._m[0][3] + _m[0][1] * o._m[1][3] + _m[0][2] * o._m[2][3] + _m[0][3] * o._m[3][3];
    // Row 2
    nMatrix._m[1][0] = _m[1][0] * o._m[0][0] + _m[1][1] * o._m[1][0] + _m[1][2] * o._m[2][0] + _m[1][3] * o._m[3][0];
    nMatrix._m[1][1] = _m[1][0] * o._m[0][1] + _m[1][1] * o._m[1][1] + _m[1][2] * o._m[2][1] + _m[1][3] * o._m[3][1];
    nMatrix._m[1][2] = _m[1][0] * o._m[0][2] + _m[1][1] * o._m[1][2] + _m[1][2] * o._m[2][2] + _m[1][3] * o._m[3][2];
    nMatrix._m[1][3] = _m[1][0] * o._m[0][3] + _m[1][1] * o._m[1][3] + _m[1][2] * o._m[2][3] + _m[1][3] * o._m[3][3];
    // Row 3
    nMatrix._m[2][0] = _m[2][0] * o._m[0][0] + _m[2][1] * o._m[1][0] + _m[2][2] * o._m[2][0] + _m[2][3] * o._m[3][0];
    nMatrix._m[2][1] = _m[2][0] * o._m[0][1] + _m[2][1] * o._m[1][1] + _m[2][2] * o._m[2][1] + _m[2][3] * o._m[3][1];
    nMatrix._m[2][2] = _m[2][0] * o._m[0][2] + _m[2][1] * o._m[1][2] + _m[2][2] * o._m[2][2] + _m[2][3] * o._m[3][2];
    nMatrix._m[2][3] = _m[2][0] * o._m[0][3] + _m[2][1] * o._m[1][3] + _m[2][2] * o._m[2][3] + _m[2][3] * o._m[3][3];
    // Row 4
    nMatrix._m[3][0] = _m[3][0] * o._m[0][0] + _m[3][1] * o._m[1][0] + _m[3][2] * o._m[2][0] + _m[3][3] * o._m[3][0];
    nMatrix._m[3][1] = _m[3][0] * o._m[0][1] + _m[3][1] * o._m[1][1] + _m[3][2] * o._m[2][1] + _m[3][3] * o._m[3][1];
    nMatrix._m[3][2] = _m[3][0] * o._m[0][2] + _m[3][1] * o._m[1][2] + _m[3][2] * o._m[2][2] + _m[3][3] * o._m[3][2];
    nMatrix._m[3][3] = _m[3][0] * o._m[0][3] + _m[3][1] * o._m[1][3] + _m[3][2] * o._m[2][3] + _m[3][3] * o._m[3][3];
    return nMatrix;
}


// -----------------------------------------------------------------------------
// Getters - Setters
// -----------------------------------------------------------------------------
void MatrixF4::set(MatrixF4 const& o){
    // Row 1
    this->_m[0][0] = o._m[0][0];
    this->_m[0][1] = o._m[0][1];
    this->_m[0][2] = o._m[0][2];
    this->_m[0][3] = o._m[0][3];
    // Row 2
    this->_m[1][0] = o._m[1][0];
    this->_m[1][1] = o._m[1][1];
    this->_m[1][2] = o._m[1][2];
    this->_m[1][3] = o._m[1][3];
    // Row 3
    this->_m[2][0] = o._m[2][0];
    this->_m[2][1] = o._m[2][1];
    this->_m[2][2] = o._m[2][2];
    this->_m[2][3] = o._m[2][3];
    // Row 4
    this->_m[3][0] = o._m[3][0];
    this->_m[3][1] = o._m[3][1];
    this->_m[3][2] = o._m[3][2];
    this->_m[3][3] = o._m[3][3];
}


// -----------------------------------------------------------------------------
// Operators overload (Inplace)
// -----------------------------------------------------------------------------
FORCE_INLINE MatrixF4& MatrixF4::operator*=(float const s) {
    // Row 1
    this->_m[0][0] = this->_m[0][0] * s;
    this->_m[0][1] = this->_m[0][1] * s;
    this->_m[0][2] = this->_m[0][2] * s;
    this->_m[0][3] = this->_m[0][3] * s;
    // Row 2
    this->_m[1][0] = this->_m[1][0] * s;
    this->_m[1][1] = this->_m[1][1] * s;
    this->_m[1][2] = this->_m[1][2] * s;
    this->_m[1][3] = this->_m[1][3] * s;
    // Row 3
    this->_m[2][0] = this->_m[2][0] * s;
    this->_m[2][1] = this->_m[2][1] * s;
    this->_m[2][2] = this->_m[2][2] * s;
    this->_m[2][3] = this->_m[2][3] * s;
    // Row 4
    this->_m[3][0] = this->_m[3][0] * s;
    this->_m[3][1] = this->_m[3][1] * s;
    this->_m[3][2] = this->_m[3][2] * s;
    this->_m[3][3] = this->_m[3][3] * s;
    return *this;
}

FORCE_INLINE MatrixF4& MatrixF4::operator*=(MatrixF4 const& o) {
    this->set(*this * o);
    return *this;
}


// -----------------------------------------------------------------------------
// Operators overload (Other)
// -----------------------------------------------------------------------------
FORCE_INLINE bool MatrixF4::operator==(MatrixF4 const& o) const {
    return
        _m[0][0] == o._m[0][0] && _m[0][1] == o._m[0][1] && _m[0][2] == o._m[0][2] && _m[0][3] == o._m[0][3] &&
        _m[1][0] == o._m[1][0] && _m[1][1] == o._m[1][1] && _m[1][2] == o._m[1][2] && _m[1][3] == o._m[1][3] &&
        _m[2][0] == o._m[2][0] && _m[2][1] == o._m[2][1] && _m[2][2] == o._m[2][2] && _m[2][3] == o._m[2][3] &&
        _m[3][0] == o._m[3][0] && _m[3][1] == o._m[3][1] && _m[3][2] == o._m[3][2] && _m[3][3] == o._m[3][3];
}

FORCE_INLINE bool MatrixF4::operator!=(MatrixF4 const& o) const {
    return
        _m[0][0] != o._m[0][0] || _m[0][1] != o._m[0][1] || _m[0][2] != o._m[0][2] || _m[0][3] != o._m[0][3] ||
        _m[1][0] != o._m[1][0] || _m[1][1] != o._m[1][1] || _m[1][2] != o._m[1][2] || _m[1][3] != o._m[1][3] ||
        _m[2][0] != o._m[2][0] || _m[2][1] != o._m[2][1] || _m[2][2] != o._m[2][2] || _m[2][3] != o._m[2][3] ||
        _m[3][0] != o._m[3][0] || _m[3][1] != o._m[3][1] || _m[3][2] != o._m[3][2] || _m[3][3] != o._m[3][3];
}


