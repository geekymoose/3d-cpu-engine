// =============================================================================
// INLINE.
// SSE Implementation (SSE 4.1). Used for Vector instead of FPU.
// Author: Constantin Masson
// =============================================================================


// -----------------------------------------------------------------------------
// Constructors
// -----------------------------------------------------------------------------
FORCE_INLINE VectF4::VectF4(void) {
    this->m128 = _mm_setzero_ps();
}

FORCE_INLINE VectF4::VectF4(const float s) {
    this->m128 = _mm_setr_ps(s,s,s,s);
}

FORCE_INLINE VectF4::VectF4(const float x, const float y, const float z, const float w) {
    this->m128 = _mm_setr_ps(x,y,z,w);
}

FORCE_INLINE VectF4::VectF4(const __m128 v) {
    this->m128 = v;
}


// -----------------------------------------------------------------------------
// Functions
// -----------------------------------------------------------------------------
FORCE_INLINE float VectF4::length() const {
    return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(this->m128, this->m128, 0xF1)));
}

FORCE_INLINE float VectF4::length3() const {
    return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(this->m128, this->m128, 0x71)));
}

FORCE_INLINE float VectF4::squareLength() const {
    return _mm_cvtss_f32(_mm_dp_ps(this->m128, this->m128, 0xF1));
}

FORCE_INLINE float VectF4::squareLength3() const {
    return _mm_cvtss_f32(_mm_dp_ps(this->m128, this->m128, 0x71));
}

FORCE_INLINE VectF4 VectF4::getNormalFast() const {
    __m128 l    = _mm_sqrt_ps(_mm_dp_ps(this->m128, this->m128, 0xFF));
    __m128 res  = _mm_div_ps(this->m128,l);
    return VectF4(res);
}

FORCE_INLINE VectF4 VectF4::getNormalFast3() const {
    __m128 l    = _mm_sqrt_ps(_mm_dp_ps(this->m128, this->m128, 0x7F));
    __m128 res  = _mm_div_ps(this->m128,l);
    res[3]      = 0.0f; // Set w to 0
    return VectF4(res);
}

FORCE_INLINE void VectF4::normalizeFast() {
    __m128 l    = _mm_sqrt_ps(_mm_dp_ps(this->m128, this->m128, 0xFF));
    __m128 res  = _mm_div_ps(this->m128,l);
    this->set(res);
}

FORCE_INLINE VectF4 VectF4::getCrossProduct(VectF4 const& v) const {
    __m128 rabit = _mm_sub_ps(
            _mm_mul_ps(
                _mm_shuffle_ps(this->m128, this->m128, _MM_SHUFFLE(3,0,2,1)),
                _mm_shuffle_ps(v.m128, v.m128, _MM_SHUFFLE(3,1,0,2))),
            _mm_mul_ps(
                _mm_shuffle_ps(this->m128, this->m128, _MM_SHUFFLE(3,1,0,2)),
                _mm_shuffle_ps(v.m128, v.m128, _MM_SHUFFLE(3,0,2,1))));
    rabit[3] = 0; // Set w to 0
    return VectF4(rabit);
}


// -----------------------------------------------------------------------------
// Static functions
// -----------------------------------------------------------------------------
FORCE_INLINE float VectF4::dotProduct(VectF4 const& v1, VectF4 const& v2) {
    return _mm_cvtss_f32(_mm_dp_ps(v1.m128, v2.m128, 0xF1));
}

FORCE_INLINE float VectF4::dotProduct3(VectF4 const& v1, VectF4 const& v2) {
    return _mm_cvtss_f32(_mm_dp_ps(v1.m128, v2.m128, 0x71));
}

FORCE_INLINE VectF4 VectF4::crossProduct(VectF4 const& v1, VectF4 const& v2) {
    __m128 rabit = _mm_sub_ps(
            _mm_mul_ps(
                _mm_shuffle_ps(v1.m128, v1.m128, _MM_SHUFFLE(3,0,2,1)),
                _mm_shuffle_ps(v2.m128, v2.m128, _MM_SHUFFLE(3,1,0,2))),
            _mm_mul_ps(
                _mm_shuffle_ps(v1.m128, v1.m128, _MM_SHUFFLE(3,1,0,2)),
                _mm_shuffle_ps(v2.m128, v2.m128, _MM_SHUFFLE(3,0,2,1))));
    rabit[3] = 0; // Set w to 0 (crossProduct only on 3 axis)
    return VectF4(rabit);
}


// -----------------------------------------------------------------------------
// Getters - Setters
// -----------------------------------------------------------------------------
FORCE_INLINE void VectF4::set(float const x, float const y, float const z, float const w) {
    this->m128 = _mm_setr_ps(x,y,z,w);
}

FORCE_INLINE void VectF4::set(VectF4 const& v) {
    this->m128 = v.m128;
}

FORCE_INLINE void VectF4::set(const __m128 v) {
    this->m128 = v;
}


// -----------------------------------------------------------------------------
// Operators overload
// -----------------------------------------------------------------------------
FORCE_INLINE VectF4 VectF4::operator*(float const s) const {
    return VectF4(_mm_mul_ps(this->m128, _mm_set_ps(s,s,s,s)));
}

FORCE_INLINE VectF4 VectF4::operator*(VectF4 const& v) const {
    return VectF4(_mm_mul_ps(this->m128, v.m128));
}

FORCE_INLINE VectF4 VectF4::operator/(float const s) const {
    return VectF4(_mm_div_ps(this->m128, _mm_set_ps(s,s,s,s)));
}

FORCE_INLINE VectF4 VectF4::operator/(VectF4 const& v) const {
    return VectF4(_mm_div_ps(this->m128, v.m128));
}

FORCE_INLINE VectF4 VectF4::operator+(float const s) const {
    return VectF4(_mm_add_ps(this->m128, _mm_set_ps(s,s,s,s)));
}

FORCE_INLINE VectF4 VectF4::operator+(VectF4 const& v) const {
    return VectF4(_mm_add_ps(this->m128, v.m128));
}

FORCE_INLINE VectF4 VectF4::operator-(float const s) const {
    return VectF4(_mm_sub_ps(this->m128, _mm_set_ps(s,s,s,s)));
}

FORCE_INLINE VectF4 VectF4::operator-(VectF4 const& v) const {
    return VectF4(_mm_sub_ps(this->m128, v.m128));
}

FORCE_INLINE VectF4& VectF4::operator*=(float const s) {
    this->m128 = _mm_mul_ps(this->m128, _mm_set_ps(s,s,s,s));
    return *this;
}

FORCE_INLINE VectF4& VectF4::operator*=(VectF4 const& v) {
    this->m128 = _mm_mul_ps(this->m128, v.m128);
    return *this;
}

FORCE_INLINE VectF4& VectF4::operator/=(float const s) {
    this->m128 = _mm_div_ps(this->m128, _mm_set_ps(s,s,s,s));
    return *this;
}

FORCE_INLINE VectF4& VectF4::operator/=(VectF4 const& v) {
    this->m128 = _mm_div_ps(this->m128, v.m128);
    return *this;
}

FORCE_INLINE VectF4& VectF4::operator+=(float const s) {
    this->m128 = _mm_add_ps(this->m128, _mm_set_ps(s,s,s,s));
    return *this;
}

FORCE_INLINE VectF4& VectF4::operator+=(VectF4 const& v) {
    this->m128 = _mm_add_ps(this->m128, v.m128);
    return *this;
}

FORCE_INLINE VectF4& VectF4::operator-=(float const s) {
    this->m128 = _mm_sub_ps(this->m128, _mm_set_ps(s,s,s,s));
    return *this;
}

FORCE_INLINE VectF4& VectF4::operator-=(VectF4 const& v) {
    this->m128 = _mm_sub_ps(this->m128, v.m128);
    return *this;
}

FORCE_INLINE bool VectF4::operator==(VectF4 const& v) const {
    __m128 res = _mm_cmpeq_ps(this->m128, v.m128);
    return _mm_movemask_ps(res);
}

FORCE_INLINE bool VectF4::operator!=(VectF4 const& v) const {
    __m128 res = _mm_cmpneq_ps(this->m128, v.m128);
    return _mm_movemask_ps(res);
}

