// =============================================================================
// INLINE.
// FPU Implementation. This is the common Vector implementation.
// =============================================================================


// -----------------------------------------------------------------------------
// Constructors
// -----------------------------------------------------------------------------
FORCE_INLINE VectF4::VectF4(void) {
    this->x = 0.0f;
    this->y = 0.0f;
    this->z = 0.0f;
    this->w = 0.0f;
}

FORCE_INLINE VectF4::VectF4(float x, float y, float z, float w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}


// -----------------------------------------------------------------------------
// Functions
// -----------------------------------------------------------------------------
FORCE_INLINE float VectF4::length() const {
    return sqrt(this->squareLength());
}

FORCE_INLINE float VectF4::length3() const {
    return sqrt(this->squareLength3());
}

FORCE_INLINE float VectF4::squareLength() const {
    return (x*x) + (y*y) + (z*z) + (w*w);
}

FORCE_INLINE float VectF4::squareLength3() const {
    return (x*x) + (y*y) + (z*z);
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
FORCE_INLINE float VectF4::dotProduct(VectF4 const& v1, VectF4 const& v2) {
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z) + (v1.w * v2.w);
}

FORCE_INLINE float VectF4::dotProduct3(VectF4 const& v1, VectF4 const& v2) {
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}


// -----------------------------------------------------------------------------
// Operators overload
// -----------------------------------------------------------------------------
FORCE_INLINE bool VectF4::operator==(VectF4 const& v) const {
    return  this->x == v.x &&
            this->y == v.y &&
            this->z == v.z &&
            this->w == v.w;
}

FORCE_INLINE bool VectF4::operator!=(VectF4 const& v) const {
    return  this->x != v.x ||
            this->y != v.y ||
            this->z != v.z ||
            this->w != v.w;
}

FORCE_INLINE VectF4 VectF4::operator*(float const s) const {
    return VectF4(x*s, y*s, z*s, w*s);
}

FORCE_INLINE VectF4 VectF4::operator/(float const s) const {
    return VectF4(x/s, y/s, z/s, w/s);
}

FORCE_INLINE VectF4 VectF4::operator+(VectF4 const& v) const {
    return VectF4(x+v.x, y+v.y, z+v.z, w+v.w);
}

FORCE_INLINE VectF4 VectF4::operator-(VectF4 const& v) const {
    return VectF4(x-v.x, y-v.y, z-v.z, w-v.w);
}

FORCE_INLINE VectF4& VectF4::operator*=(float const s) {
    this->x = this->x * s;
    this->y = this->y * s;
    this->z = this->z * s;
    this->w = this->w * s;
    return *this;
}

FORCE_INLINE VectF4& VectF4::operator/=(float const s) {
    this->x = this->x / s;
    this->y = this->y / s;
    this->z = this->z / s;
    this->w = this->w / s;
    return *this;
}

FORCE_INLINE VectF4& VectF4::operator+=(VectF4 const& v) {
    this->x = this->x + v.x;
    this->y = this->y + v.y;
    this->z = this->z + v.z;
    this->w = this->w + v.w;
    return *this;
}

FORCE_INLINE VectF4& VectF4::operator-=(VectF4 const& v) {
    this->x = this->x - v.x;
    this->y = this->y - v.y;
    this->z = this->z - v.z;
    this->w = this->w - v.w;
    return *this;
}
