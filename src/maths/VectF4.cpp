#include "VectF4.h"


// -----------------------------------------------------------------------------
// VectF4 Constructors
// -----------------------------------------------------------------------------
VectF4::VectF4(void) :x(0.0f), y(0.0f), z(0.0f), w(0.0f) {};

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

float VectF4::length3() const {
    return sqrt(this->squareLength3());
}

float VectF4::squareLength() const {
    return (x*x) + (y*y) + (z*z) + (w*w);
}

float VectF4::squareLength3() const {
    return (x*x) + (y*y) + (z*z);
}

VectF4 VectF4::normalize() const {
    float l = this->length();
    VectF4 v(x/l, y/l, z/l, w/l);
    return v;
}

VectF4 VectF4::normalize3() const {
    float l = this->length3();
    VectF4 v(x/l, y/l, z/l, 0.0f);
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

float VectF4::dotProduct(VectF4 const& v1, VectF4 const& v2) {
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z) + (v1.w * v2.w);
}

float VectF4::dotProduct3(VectF4 const& v1, VectF4 const& v2) {
    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
}


// -----------------------------------------------------------------------------
// VectF4 Operators overload
// -----------------------------------------------------------------------------
bool VectF4::operator==(VectF4 const& v) const{
    return  this->x == v.x &&
            this->y == v.y &&
            this->z == v.z &&
            this->w == v.w;
}
bool VectF4::operator!=(VectF4 const& v) const{
    return  this->x != v.x ||
            this->y != v.y ||
            this->z != v.z ||
            this->w != v.w;
}
VectF4 VectF4::operator*(float const s) const{
    return VectF4(x*s, y*s, z*s, w*s);
}
VectF4 VectF4::operator/(float const s) const{
    return VectF4(x/s, y/s, z/s, w/s);
}
VectF4 VectF4::operator+(VectF4 const& v) const{
    return VectF4(x+v.x, y+v.y, z+v.z, w+v.w);
}
VectF4 VectF4::operator-(VectF4 const& v) const{
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
std::ostream& operator<<(std::ostream &os, VectF4 const& v){
    os << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
    return os;
}
