/*
 * Inline function defintions of VectF4
 * Should be included by VectF4.h only
 */


// -----------------------------------------------------------------------------
// Constructors
// -----------------------------------------------------------------------------
FORCE_INLINE VectF4::VectF4(void){
#ifdef __SSE4_1__
    this->m128 = _mm_setzero_ps();
#else
    this->x = 0.0f;
    this->y = 0.0f;
    this->z = 0.0f;
    this->w = 0.0f;
#endif
}

FORCE_INLINE VectF4::VectF4(float x, float y, float z, float w){
#ifdef __SSE4_1__
    this->m128 = _mm_setr_ps(x,y,z,w);
#else
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
#endif
}

#ifdef __SSE4_1__
FORCE_INLINE VectF4::VectF4(__m128 v){
    this->m128 = v;
}
#endif


// -----------------------------------------------------------------------------
// Functions
// -----------------------------------------------------------------------------
FORCE_INLINE float VectF4::length() const {
#ifdef __SSE4_1__
    return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(this->m128,this->m128,0xF1)));
#else
    return sqrt(this->squareLength());
#endif
}

FORCE_INLINE float VectF4::length3() const {
#ifdef __SSE4_1__
    return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(this->m128,this->m128,0x71)));
#else
    return sqrt(this->squareLength3());
#endif
}

FORCE_INLINE float VectF4::squareLength() const {
#ifdef __SSE4_1__
    return _mm_cvtss_f32(_mm_dp_ps(this->m128,this->m128,0xF1));
#else
    return (x*x) + (y*y) + (z*z) + (w*w);
#endif
}

FORCE_INLINE float VectF4::squareLength3() const {
#ifdef __SSE4_1__
    return _mm_cvtss_f32(_mm_dp_ps(this->m128,this->m128,0x71));
#else
    return (x*x) + (y*y) + (z*z);
#endif
}

FORCE_INLINE VectF4 VectF4::normalize() const {
#ifdef __SSE4_1__
    __m128 l    = _mm_sqrt_ps(_mm_dp_ps(this->m128,this->m128,0xFF));
    __m128 res  = _mm_div_ps(this->m128,l);
    return VectF4(res);
#else
    float l = this->length();
    VectF4 v(x/l, y/l, z/l, w/l);
    return v;
#endif
}

FORCE_INLINE VectF4 VectF4::normalize3() const {
#ifdef __SSE4_1__
    __m128 l    = _mm_sqrt_ps(_mm_dp_ps(this->m128,this->m128,0x7F));
    __m128 res  = _mm_div_ps(this->m128,l);
    res[3]      = 0.0f; // Set w to 0
    return VectF4(res);
#else
    float l = this->length3();
    VectF4 v(x/l, y/l, z/l, 0.0f);
    return v;
#endif
}

FORCE_INLINE VectF4 VectF4::crossProduct3(VectF4 const& v) const {
#ifdef __SSE4_1__
    __m128 rabit = _mm_sub_ps(
            _mm_mul_ps(
                _mm_shuffle_ps(this->m128, this->m128, _MM_SHUFFLE(3,0,2,1)),
                _mm_shuffle_ps(v.m128, v.m128, _MM_SHUFFLE(3,1,0,2))),
            _mm_mul_ps(
                _mm_shuffle_ps(this->m128, this->m128, _MM_SHUFFLE(3,1,0,2)),
                _mm_shuffle_ps(v.m128, v.m128, _MM_SHUFFLE(3,0,2,1))));
    rabit[3] = 0; // Set w to 0
    return VectF4(rabit);
#else
    return VectF4(
        (y*v.z) - (z*v.y),
        (z*v.x) - (x*v.z),
        (x*v.y) - (y*v.x),
        0.0f
    );
#endif
}


// -----------------------------------------------------------------------------
// Getters - Setters
// -----------------------------------------------------------------------------
FORCE_INLINE void VectF4::set(float const x, float const y, float const z, float const w) {
#ifdef __SSE4_1__
    this->m128 = _mm_setr_ps(x,y,z,w);
#else
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
#endif
}

FORCE_INLINE void VectF4::set(VectF4 const& v) {
#ifdef __SSE4_1__
    this->m128 = v.m128;
#else
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
    this->w = v.w;
#endif
}


// -----------------------------------------------------------------------------
// Static functions
// -----------------------------------------------------------------------------
float VectF4::dotProduct(VectF4 const& v1, VectF4 const& v2) {
#ifdef __SSE4_1__
    return _mm_cvtss_f32(_mm_dp_ps(v1.m128,v2.m128,0xF1));
#else
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z) + (v1.w * v2.w);
#endif
}

float VectF4::dotProduct3(VectF4 const& v1, VectF4 const& v2) {
#ifdef __SSE4_1__
    return _mm_cvtss_f32(_mm_dp_ps(v1.m128,v2.m128,0x71));
#else
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
#endif
}


// -----------------------------------------------------------------------------
// Operators overload
// -----------------------------------------------------------------------------
FORCE_INLINE bool VectF4::operator==(VectF4 const& v) const{
#ifdef __SSE4_1__
    __m128 res = _mm_cmpeq_ps(this->m128, v.m128);
    return _mm_movemask_ps(res);
#else
    return  this->x == v.x &&
            this->y == v.y &&
            this->z == v.z &&
            this->w == v.w;
#endif
}

FORCE_INLINE bool VectF4::operator!=(VectF4 const& v) const{
#ifdef __SSE4_1__
    __m128 res = _mm_cmpneq_ps(this->m128, v.m128);
    return _mm_movemask_ps(res);
#else
    return  this->x != v.x ||
            this->y != v.y ||
            this->z != v.z ||
            this->w != v.w;
#endif
}

FORCE_INLINE VectF4 VectF4::operator*(float const s) const{
#ifdef __SSE4_1__
    return VectF4(this->m128 * s);
#else
    return VectF4(x*s, y*s, z*s, w*s);
#endif
}

FORCE_INLINE VectF4 VectF4::operator/(float const s) const{
#ifdef __SSE4_1__
    return VectF4(this->m128 / s);
#else
    return VectF4(x/s, y/s, z/s, w/s);
#endif
}

FORCE_INLINE VectF4 VectF4::operator+(VectF4 const& v) const{
#ifdef __SSE4_1__
    return VectF4(this->m128 + v.m128);
#else
    return VectF4(x+v.x, y+v.y, z+v.z, w+v.w);
#endif
}

FORCE_INLINE VectF4 VectF4::operator-(VectF4 const& v) const{
#ifdef __SSE4_1__
    return VectF4(this->m128 - v.m128);
#else
    return VectF4(x-v.x, y-v.y, z-v.z, w-v.w);
#endif
}

FORCE_INLINE VectF4& VectF4::operator*=(float const s){
#ifdef __SSE4_1__
    this->m128 = this->m128 * s;
#else
    this->x = this->x * s;
    this->y = this->y * s;
    this->z = this->z * s;
    this->w = this->w * s;
#endif
    return *this;
}

FORCE_INLINE VectF4& VectF4::operator/=(float const s){
#ifdef __SSE4_1__
    this->m128 = this->m128 / s;
#else
    this->x = this->x / s;
    this->y = this->y / s;
    this->z = this->z / s;
    this->w = this->w / s;
#endif
    return *this;
}

FORCE_INLINE VectF4& VectF4::operator+=(VectF4 const& v){
#ifdef __SSE4_1__
    this->m128 = this->m128 + v.m128;
#else
    this->x = this->x + v.x;
    this->y = this->y + v.y;
    this->z = this->z + v.z;
    this->w = this->w + v.w;
#endif
    return *this;
}

FORCE_INLINE VectF4& VectF4::operator-=(VectF4 const& v){
#ifdef __SSE4_1__
    this->m128 = this->m128 - v.m128;
#else
    this->x = this->x - v.x;
    this->y = this->y - v.y;
    this->z = this->z - v.z;
    this->w = this->w - v.w;
#endif
    return *this;
}

FORCE_INLINE std::ostream& operator<<(std::ostream &os, VectF4 const& v){
    os << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
    return os;
}


