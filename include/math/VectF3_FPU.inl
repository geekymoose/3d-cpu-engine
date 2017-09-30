// =============================================================================
// INLINE.
// FPU Implementation. This is the common Vector implementation.
// Author: Constantin Masson
// =============================================================================


// -----------------------------------------------------------------------------
// Constructors
// -----------------------------------------------------------------------------
FORCE_INLINE VectF3::VectF3() {
    this->x = 0.0f;
    this->y = 0.0f;
    this->z = 0.0f;
}

FORCE_INLINE VectF3::VectF3(const float s) {
    this->x = s;
    this->y = s;
    this->z = s;
}

FORCE_INLINE VectF3::VectF3(const float x, const float y, const float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}


// -----------------------------------------------------------------------------
// Functions
// -----------------------------------------------------------------------------
FORCE_INLINE float VectF3::length() const {
    return sqrt(this->squareLength());
}

FORCE_INLINE float VectF3::squareLength() const {
    return (x*x) + (y*y) + (z*z);
}

FORCE_INLINE VectF3 VectF3::getNormalFast() const {
    float l = this->length();
    VectF3 v(x/l, y/l, z/l);
    return v;
}

FORCE_INLINE void VectF3::normalizeFast() {
    float l = this->length();
    this->set(x/l, y/l, z/l);
}

FORCE_INLINE VectF3 VectF3::getCrossProduct(VectF3 const& v) const {
    return VectF3(
        (y * v.z) - (z * v.y),
        (z * v.x) - (x * v.z),
        (x * v.y) - (y * v.x)
    );
}


// -----------------------------------------------------------------------------
// Static functions
// -----------------------------------------------------------------------------
FORCE_INLINE float VectF3::dotProduct(VectF3 const& v1, VectF3 const& v2) {
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}

FORCE_INLINE VectF3 VectF3::crossProduct(VectF3 const& v1, VectF3 const& v2) {
    return VectF3(
        (v1.y * v2.z) - (v1.z * v2.y),
        (v1.z * v2.x) - (v1.x * v2.z),
        (v1.x * v2.y) - (v1.y * v2.x)
    );
}


// -----------------------------------------------------------------------------
// Getters - Setters
// -----------------------------------------------------------------------------
FORCE_INLINE void VectF3::set(float const x, float const y, float const z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

FORCE_INLINE void VectF3::set(VectF3 const& v) {
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
}


// -----------------------------------------------------------------------------
// Operators overload
// -----------------------------------------------------------------------------
FORCE_INLINE VectF3 VectF3::operator*(float const s) const {
    return VectF3(x*s, y*s, z*s);
}

FORCE_INLINE VectF3 VectF3::operator*(VectF3 const& v) const {
    return VectF3(x*v.x, y*v.y, z*v.z);
}

FORCE_INLINE VectF3 VectF3::operator/(float const s) const {
    return VectF3(x/s, y/s, z/s);
}

FORCE_INLINE VectF3 VectF3::operator/(VectF3 const& v) const {
    return VectF3(x/v.x, y/v.y, z/v.z);
}

FORCE_INLINE VectF3 VectF3::operator+(float const s) const {
    return VectF3(x+s, y+s, z+s);
}

FORCE_INLINE VectF3 VectF3::operator+(VectF3 const& v) const {
    return VectF3(x+v.x, y+v.y, z+v.z);
}

FORCE_INLINE VectF3 VectF3::operator-(float const s) const {
    return VectF3(x-s, y-s, z-s);
}

FORCE_INLINE VectF3 VectF3::operator-(VectF3 const& v) const {
    return VectF3(x-v.x, y-v.y, z-v.z);
}

FORCE_INLINE VectF3& VectF3::operator*=(float const s) {
    this->x = this->x * s;
    this->y = this->y * s;
    this->z = this->z * s;
    return *this;
}

FORCE_INLINE VectF3& VectF3::operator*=(VectF3 const& v) {
    this->x = this->x * v.x;
    this->y = this->y * v.y;
    this->z = this->z * v.z;
    return *this;
}

FORCE_INLINE VectF3& VectF3::operator/=(float const s) {
    this->x = this->x / s;
    this->y = this->y / s;
    this->z = this->z / s;
    return *this;
}

FORCE_INLINE VectF3& VectF3::operator/=(VectF3 const& v) {
    this->x = this->x / v.x;
    this->y = this->y / v.y;
    this->z = this->z / v.z;
    return *this;
}

FORCE_INLINE VectF3& VectF3::operator+=(float const s) {
    this->x = this->x + s;
    this->y = this->y + s;
    this->z = this->z + s;
    return *this;
}

FORCE_INLINE VectF3& VectF3::operator+=(VectF3 const& v) {
    this->x = this->x + v.x;
    this->y = this->y + v.y;
    this->z = this->z + v.z;
    return *this;
}

FORCE_INLINE VectF3& VectF3::operator-=(float const s) {
    this->x = this->x - s;
    this->y = this->y - s;
    this->z = this->z - s;
    return *this;
}

FORCE_INLINE VectF3& VectF3::operator-=(VectF3 const& v) {
    this->x = this->x - v.x;
    this->y = this->y - v.y;
    this->z = this->z - v.z;
    return *this;
}

FORCE_INLINE bool VectF3::operator==(VectF3 const& v) const {
    return  this->x == v.x &&
            this->y == v.y &&
            this->z == v.z;
}

FORCE_INLINE bool VectF3::operator!=(VectF3 const& v) const {
    return  this->x != v.x ||
            this->y != v.y ||
            this->z != v.z;
}

