/*
 * Inline function defintions of VectF3
 * Should be included by VectF3.h only
 */


// -----------------------------------------------------------------------------
// Constructors
// -----------------------------------------------------------------------------
FORCE_INLINE VectF3::VectF3(void){
#ifdef __SSE4_1__
    this->m128 = _mm_setzero_ps();
#else
    this->x = 0.0f;
    this->y = 0.0f;
    this->z = 0.0f;
#endif
}

FORCE_INLINE VectF3::VectF3(float x, float y, float z){
#ifdef __SSE4_1__
    this->m128 = _mm_setr_ps(x,y,z,0.0f);
#else
    this->x = x;
    this->y = y;
    this->z = z;
#endif
}

#ifdef __SSE4_1__
FORCE_INLINE VectF3::VectF3(__m128 v){
    this->m128 = v;
}
#endif


// -----------------------------------------------------------------------------
// Functions
// -----------------------------------------------------------------------------
FORCE_INLINE float VectF3::length() const {
#ifdef __SSE4_1__
    return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(this->m128, this->m128, 0x71)));
#else
    return sqrt(this->squareLength());
#endif
}

FORCE_INLINE float VectF3::squareLength() const {
#ifdef __SSE4_1__
    return _mm_cvtss_f32(_mm_dp_ps(this->m128, this->m128, 0x71));
#else
    return (x*x) + (y*y) + (z*z);
#endif
}

FORCE_INLINE VectF3 VectF3::normalize() const {
#ifdef __SSE4_1__
    __m128 l    = _mm_sqrt_ps(_mm_dp_ps(this->m128, this->m128, 0x7F));
    __m128 res  = _mm_div_ps(this->m128,l);
    res[3]      = 0.0f; // Set w to 0 (Unused)
    return VectF3(res);
#else
    float l = this->length();
    VectF3 v(x/l, y/l, z/l);
    return v;
#endif
}

FORCE_INLINE VectF3 VectF3::crossProduct(VectF3 const& v) const {
#ifdef __SSE4_1__
    __m128 rabit = _mm_sub_ps(
            _mm_mul_ps(
                _mm_shuffle_ps(this->m128, this->m128, _MM_SHUFFLE(3,0,2,1)),
                _mm_shuffle_ps(v.m128, v.m128, _MM_SHUFFLE(3,1,0,2))),
            _mm_mul_ps(
                _mm_shuffle_ps(this->m128, this->m128, _MM_SHUFFLE(3,1,0,2)),
                _mm_shuffle_ps(v.m128, v.m128, _MM_SHUFFLE(3,0,2,1))));
    rabit[3] = 0; // Set w to 0
    return VectF3(rabit);
#else
    return VectF3(
        (y*v.z) - (z*v.y),
        (z*v.x) - (x*v.z),
        (x*v.y) - (y*v.x)
    );
#endif
}


// -----------------------------------------------------------------------------
// Getters - Setters
// -----------------------------------------------------------------------------
FORCE_INLINE void VectF3::set(float const x, float const y, float const z) {
#ifdef __SSE4_1__
    this->m128 = _mm_setr_ps(x,y,z,0.0f);
#else
    this->x = x;
    this->y = y;
    this->z = z;
#endif
}

FORCE_INLINE void VectF3::set(VectF3 const& v) {
#ifdef __SSE4_1__
    this->m128 = v.m128;
#else
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
#endif
}


// -----------------------------------------------------------------------------
// Static functions
// -----------------------------------------------------------------------------
FORCE_INLINE float VectF3::dotProduct(VectF3 const& v1, VectF3 const& v2) {
#ifdef __SSE4_1__
    return _mm_cvtss_f32(_mm_dp_ps(v1.m128, v2.m128, 0x71));
#else
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
#endif
}


// -----------------------------------------------------------------------------
// Operators overload
// -----------------------------------------------------------------------------
FORCE_INLINE bool VectF3::operator==(VectF3 const& v) const{
#ifdef __SSE4_1__
    __m128 res = _mm_cmpeq_ps(this->m128, v.m128);
    res[3] = 0xffffffff; // This is just in case of w has been altered (For any strange raison)
    return _mm_movemask_ps(res);
#else
    return  this->x == v.x &&
            this->y == v.y &&
            this->z == v.z;
#endif
}

FORCE_INLINE bool VectF3::operator!=(VectF3 const& v) const{
#ifdef __SSE4_1__
    __m128 res = _mm_cmpneq_ps(this->m128, v.m128);
    res[3] = 0xffffffff; // This is just in case of w has been altered (For any strange raison)
    return _mm_movemask_ps(res);
#else
    return  this->x != v.x ||
            this->y != v.y ||
            this->z != v.z;
#endif
}

FORCE_INLINE VectF3 VectF3::operator*(float const s) const{
#ifdef __SSE4_1__
    return VectF3(this->m128 * s);
#else
    return VectF3(x*s, y*s, z*s);
#endif
}

FORCE_INLINE VectF3 VectF3::operator/(float const s) const{
#ifdef __SSE4_1__
    return VectF3(this->m128 / s);
#else
    return VectF3(x/s, y/s, z/s);
#endif
}

FORCE_INLINE VectF3 VectF3::operator+(VectF3 const& v) const{
#ifdef __SSE4_1__
    return VectF3(this->m128 + v.m128);
#else
    return VectF3(x+v.x, y+v.y, z+v.z);
#endif
}

FORCE_INLINE VectF3 VectF3::operator-(VectF3 const& v) const{
#ifdef __SSE4_1__
    return VectF3(this->m128 - v.m128);
#else
    return VectF3(x-v.x, y-v.y, z-v.z);
#endif
}

FORCE_INLINE VectF3& VectF3::operator*=(float const s){
#ifdef __SSE4_1__
    this->m128 = this->m128 * s;
#else
    this->x = this->x * s;
    this->y = this->y * s;
    this->z = this->z * s;
#endif
    return *this;
}

FORCE_INLINE VectF3& VectF3::operator/=(float const s){
#ifdef __SSE4_1__
    this->m128 = this->m128 / s;
#else
    this->x = this->x / s;
    this->y = this->y / s;
    this->z = this->z / s;
#endif
    return *this;
}

FORCE_INLINE VectF3& VectF3::operator+=(VectF3 const& v){
#ifdef __SSE4_1__
    this->m128 = this->m128 + v.m128;
#else
    this->x = this->x + v.x;
    this->y = this->y + v.y;
    this->z = this->z + v.z;
#endif
    return *this;
}

FORCE_INLINE VectF3& VectF3::operator-=(VectF3 const& v){
#ifdef __SSE4_1__
    this->m128 = this->m128 - v.m128;
#else
    this->x = this->x - v.x;
    this->y = this->y - v.y;
    this->z = this->z - v.z;
#endif
    return *this;
}

FORCE_INLINE std::ostream& operator<<(std::ostream &os, VectF3 const& v){
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}


