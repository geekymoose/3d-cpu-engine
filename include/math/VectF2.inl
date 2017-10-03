// =============================================================================
// INLINE.
// Vector 2 function definitions.
// Author: Constantin Masson
// =============================================================================


// -----------------------------------------------------------------------------
// Constructors
// -----------------------------------------------------------------------------
FORCE_INLINE VectF2::VectF2() {
    this->x = 0.0f;
    this->y = 0.0f;
}

FORCE_INLINE VectF2::VectF2(const float s) {
    this->x = s;
    this->y = s;
}

FORCE_INLINE VectF2::VectF2(const float x, const float y) {
    this->x = x;
    this->y = y;
}


// -----------------------------------------------------------------------------
// Functions
// -----------------------------------------------------------------------------
FORCE_INLINE float VectF2::length() const {
    return sqrt(this->squareLength());
}

FORCE_INLINE float VectF2::squareLength() const {
    return (x*x) + (y*y);
}

FORCE_INLINE VectF2 VectF2::getNormalFast() const {
    float l = this->length();
    VectF2 v(x/l, y/l);
    return v;
}

FORCE_INLINE void VectF2::normalizeFast() {
    float l = this->length();
    this->set(x/l, y/l);
}


// -----------------------------------------------------------------------------
// Static functions
// -----------------------------------------------------------------------------
FORCE_INLINE float VectF2::dotProduct(VectF2 const& v1, VectF2 const& v2) {
    return (v1.x * v2.x) + (v1.y * v2.y);
}


// -----------------------------------------------------------------------------
// Getters - Setters
// -----------------------------------------------------------------------------
FORCE_INLINE void VectF2::set(float const x, float const y) {
    this->x = x;
    this->y = y;
}

FORCE_INLINE void VectF2::set(VectF2 const& v) {
    this->x = v.x;
    this->y = v.y;
}


// -----------------------------------------------------------------------------
// Operators overload
// -----------------------------------------------------------------------------
FORCE_INLINE VectF2 VectF2::operator*(float const s) const {
    return VectF2(x*s, y*s);
}

FORCE_INLINE VectF2 VectF2::operator*(VectF2 const& v) const {
    return VectF2(x*v.x, y*v.y);
}

FORCE_INLINE VectF2 VectF2::operator/(float const s) const {
    return VectF2(x/s, y/s);
}

FORCE_INLINE VectF2 VectF2::operator/(VectF2 const& v) const {
    return VectF2(x/v.x, y/v.y);
}

FORCE_INLINE VectF2 VectF2::operator+(float const s) const {
    return VectF2(x+s, y+s);
}

FORCE_INLINE VectF2 VectF2::operator+(VectF2 const& v) const {
    return VectF2(x+v.x, y+v.y);
}

FORCE_INLINE VectF2 VectF2::operator-(float const s) const {
    return VectF2(x-s, y-s);
}

FORCE_INLINE VectF2 VectF2::operator-(VectF2 const& v) const {
    return VectF2(x-v.x, y-v.y);
}

FORCE_INLINE VectF2& VectF2::operator*=(float const s) {
    this->x = this->x * s;
    this->y = this->y * s;
    return *this;
}

FORCE_INLINE VectF2& VectF2::operator*=(VectF2 const& v) {
    this->x = this->x * v.x;
    this->y = this->y * v.y;
    return *this;
}

FORCE_INLINE VectF2& VectF2::operator/=(float const s) {
    this->x = this->x / s;
    this->y = this->y / s;
    return *this;
}

FORCE_INLINE VectF2& VectF2::operator/=(VectF2 const& v) {
    this->x = this->x / v.x;
    this->y = this->y / v.y;
    return *this;
}

FORCE_INLINE VectF2& VectF2::operator+=(float const s) {
    this->x = this->x + s;
    this->y = this->y + s;
    return *this;
}

FORCE_INLINE VectF2& VectF2::operator+=(VectF2 const& v) {
    this->x = this->x + v.x;
    this->y = this->y + v.y;
    return *this;
}

FORCE_INLINE VectF2& VectF2::operator-=(float const s) {
    this->x = this->x - s;
    this->y = this->y - s;
    return *this;
}

FORCE_INLINE VectF2& VectF2::operator-=(VectF2 const& v) {
    this->x = this->x - v.x;
    this->y = this->y - v.y;
    return *this;
}

FORCE_INLINE bool VectF2::operator==(VectF2 const& v) const {
    return this->x == v.x && this->y == v.y;
}

FORCE_INLINE bool VectF2::operator!=(VectF2 const& v) const {
    return !(*this == v);
}


// -----------------------------------------------------------------------------
// Operators overload
// -----------------------------------------------------------------------------
FORCE_INLINE std::ostream& operator<<(std::ostream &os, VectF2 const& v) {
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}

FORCE_INLINE float VectF2::operator[](const size_t index) const {
    return (&x)[index];
}

FORCE_INLINE float& VectF2::operator[](const size_t index){
    return (&x)[index];
}

