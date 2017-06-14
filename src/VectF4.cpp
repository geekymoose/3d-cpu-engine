#include "VectF4.h"


// -----------------------------------------------------------------------------
// VectF4 Constructors
// -----------------------------------------------------------------------------
VectF4::VectF4() :x(0.0), y(0.0), z(0.0), w(0.0) {};

VectF4::VectF4(float x, float y, float z, float w) 
    : x(x),
      y(y),
      z(z),
      w(w) {
}

VectF4::VectF4(VectF4 const& v)
    : x(v.x),
      y(v.y),
      z(v.z),
      w(v.w) {
};


// -----------------------------------------------------------------------------
// VectF4 functions
// -----------------------------------------------------------------------------
float VectF4::length() const {
    return sqrt(this->squareLength());
}

float VectF4::squareLength() const {
    return (x*x) + (y*y) + (z*z) + (w*w);
}

void VectF4::normalize() {
    float l = this->length();
    this->x = x/l;
    this->y = y/l;
    this->z = z/l;
    this->w = w/l;
}

VectF4 VectF4::getUnitVect() const {
    VectF4 v;
    v.normalize();
    return v;
}

void VectF4::set(float const x, float const y, float const z, float const w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}
void VectF4::set(VectF4 const& v) {
    this->x = v.x;
    this->y = v.y;
    this->z = v.z;
    this->w = v.w;
}

// -----------------------------------------------------------------------------
// VectF4 Operators overload
// -----------------------------------------------------------------------------
bool VectF4::operator==(VectF4 const& v){
    return  this->x == v.x &&
            this->y == v.y &&
            this->z == v.z &&
            this->w == v.w;
}
bool VectF4::operator!=(VectF4 const& v){
    return  this->x != v.x ||
            this->y != v.y ||
            this->z != v.z ||
            this->w != v.w;
}
VectF4 VectF4::operator*(float const s) {
    return VectF4(x*s, y*s, z*s, w*s);
}
VectF4 VectF4::operator/(float const s) {
    return VectF4(x/s, y/s, z/s, w/s);
}
VectF4 VectF4::operator+(VectF4 const& v){
    return VectF4(x+v.x, y+v.y, z+v.z, w+v.w);
}
VectF4 VectF4::operator-(VectF4 const& v){
    return VectF4(x-v.x, y-v.y, z-v.z, w-v.w);
}

VectF4& VectF4::operator*=(float const s){
    this->x = this->x * s;
    this->y = this->y * s;
    this->z = this->z * s;
    this->w = this->w * s;
    return *this;
}
VectF4& VectF4::operator/=(float const s){
    this->x = this->x / s;
    this->y = this->y / s;
    this->z = this->z / s;
    this->w = this->w / s;
    return *this;
}
VectF4& VectF4::operator+=(VectF4 const& v){
    this->x = this->x + v.x;
    this->y = this->y + v.y;
    this->z = this->z + v.z;
    this->w = this->w + v.w;
    return *this;
}
VectF4& VectF4::operator-=(VectF4 const& v){
    this->x = this->x - v.x;
    this->y = this->y - v.y;
    this->z = this->z - v.z;
    this->w = this->w - v.w;
    return *this;
}
