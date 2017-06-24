/*
 * Inline function defintions of VectF4
 * Should be included by VectF4.h
 *
 */


// -----------------------------------------------------------------------------
// Constructors
// -----------------------------------------------------------------------------
FORCE_INLINE VectF4::VectF4(void){
#ifdef __SSE4_1__
    this->v = _mm_setzero_ps();
#else
    this->x = 0.0f;
    this->y = 0.0f;
    this->z = 0.0f;
    this->w = 0.0f;
#endif
}

FORCE_INLINE VectF4::VectF4(float x, float y, float z, float w){
#ifdef __SSE4_1__
    this->v = _mm_setr_ps(x,y,z,w);
#else
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
#endif
}


// -----------------------------------------------------------------------------
// Functions
// -----------------------------------------------------------------------------
FORCE_INLINE float VectF4::length() const {
#ifdef __SSE4_1__
    return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(v,v,0xF1)));
#else
    return sqrt(this->squareLength());
#endif
}

FORCE_INLINE float VectF4::length3() const {
#ifdef __SSE4_1__
    return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(v,v,0x71)));
#else
    return sqrt(this->squareLength3());
#endif
}

FORCE_INLINE float VectF4::squareLength() const {
#ifdef __SSE4_1__
    return _mm_cvtss_f32(_mm_dp_ps(v,v,0xF1));
#else
    return (x*x) + (y*y) + (z*z) + (w*w);
#endif
}

FORCE_INLINE float VectF4::squareLength3() const {
#ifdef __SSE4_1__
    return _mm_cvtss_f32(_mm_dp_ps(v,v,0x71));
#else
    return (x*x) + (y*y) + (z*z);
#endif
}

FORCE_INLINE VectF4 VectF4::normalize() const {
    float l = this->length();
    VectF4 v(x/l, y/l, z/l, w/l);
    return v;
}

FORCE_INLINE VectF4 VectF4::normalize3() const {
    float l = this->length3();
    VectF4 v(x/l, y/l, z/l, 0.0f);
    return v;
}

FORCE_INLINE VectF4 VectF4::crossProduct3(VectF4 const& v) const {
    return VectF4(
        (y*v.z) - (z*v.y),
        (z*v.x) - (x*v.z),
        (x*v.y) - (y*v.x),
        0.0f
    );
}


// -----------------------------------------------------------------------------
// Getters - Setters
// -----------------------------------------------------------------------------
FORCE_INLINE void VectF4::set(float const x, float const y, float const z, float const w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

FORCE_INLINE void VectF4::set(VectF4 const& v) {
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
    this->w = v.w;
}


// -----------------------------------------------------------------------------
// Static functions
// -----------------------------------------------------------------------------
float VectF4::dotProduct(VectF4 const& v1, VectF4 const& v2) {
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z) + (v1.w * v2.w);
}

float VectF4::dotProduct3(VectF4 const& v1, VectF4 const& v2) {
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}


// -----------------------------------------------------------------------------
// Operators overload
// -----------------------------------------------------------------------------
FORCE_INLINE bool VectF4::operator==(VectF4 const& v) const{
    return  this->x == v.x &&
            this->y == v.y &&
            this->z == v.z &&
            this->w == v.w;
}

FORCE_INLINE bool VectF4::operator!=(VectF4 const& v) const{
    return  this->x != v.x ||
            this->y != v.y ||
            this->z != v.z ||
            this->w != v.w;
}

FORCE_INLINE VectF4 VectF4::operator*(float const s) const{
    return VectF4(x*s, y*s, z*s, w*s);
}

FORCE_INLINE VectF4 VectF4::operator/(float const s) const{
    return VectF4(x/s, y/s, z/s, w/s);
}

FORCE_INLINE VectF4 VectF4::operator+(VectF4 const& v) const{
    return VectF4(x+v.x, y+v.y, z+v.z, w+v.w);
}

FORCE_INLINE VectF4 VectF4::operator-(VectF4 const& v) const{
    return VectF4(x-v.x, y-v.y, z-v.z, w-v.w);
}

FORCE_INLINE VectF4& VectF4::operator*=(float const s){
    this->x = this->x * s;
    this->y = this->y * s;
    this->z = this->z * s;
    this->w = this->w * s;
    return *this;
}

FORCE_INLINE VectF4& VectF4::operator/=(float const s){
    this->x = this->x / s;
    this->y = this->y / s;
    this->z = this->z / s;
    this->w = this->w / s;
    return *this;
}

FORCE_INLINE VectF4& VectF4::operator+=(VectF4 const& v){
    this->x = this->x + v.x;
    this->y = this->y + v.y;
    this->z = this->z + v.z;
    this->w = this->w + v.w;
    return *this;
}

FORCE_INLINE VectF4& VectF4::operator-=(VectF4 const& v){
    this->x = this->x - v.x;
    this->y = this->y - v.y;
    this->z = this->z - v.z;
    this->w = this->w - v.w;
    return *this;
}

FORCE_INLINE std::ostream& operator<<(std::ostream &os, VectF4 const& v){
    os << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
    return os;
}
