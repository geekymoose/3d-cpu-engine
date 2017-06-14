#ifndef ENGINE_MATHS_VECTF4_H_
#define ENGINE_MATHS_VECTF4_H_

#include <iostream>
#include <cmath>

/**
 * 4 Dimensions vector with float precision.
 *
 * \since   Jun 4, 2017
 * \author  Constantin MASSON
 */
class VectF4 {
    // -------------------------------------------------------------------------
    // Attributes
    // -------------------------------------------------------------------------
    public:
        float x;
        float y;
        float z;
        float w;


    // -------------------------------------------------------------------------
    // Constructors
    // -------------------------------------------------------------------------
    public:
        VectF4(void);
        explicit VectF4(float x, float y, float z, float w);


    // -------------------------------------------------------------------------
    // Functions
    // -------------------------------------------------------------------------
    public:
        /**
         * Get the length of this vector.
         *
         * \return The length (Magnitude) of this vector.
         */
        float length() const;

        /**
         * Get the length of this vector without W axis.
         *
         * \return The length (Magnitude) of this vector.
         */
        float length3() const;

        /**
         * Get the square length of this vector.
         *
         *\return The square length (Magnitude) of this vector.
         */
        float squareLength() const;

        /**
         * Get the square length of this vector without W axis.
         *
         *\return The square length (Magnitude) of this vector.
         */
        float squareLength3() const;

        /**
         * Returns a normalized copy of this vector
         * Vector shouldn't be null (No check done here).
         *
         * \return The normalized vector.
         */
        VectF4 normalize() const;

        /**
         * Returns a normalized copy of this vector without taking W axis into account.
         * Vector shouldn't be null (No check done here).
         * W axis is set to 0.
         *
         * \return The normalized vector.
         */
        VectF4 normalize3() const;


    // -------------------------------------------------------------------------
    // Getters - Setters
    // -------------------------------------------------------------------------
    public:
        /**
         * Reset all axis value of this vector.
         *
         * \param x New x coordinate.
         * \param y New y coordinate.
         * \param z New z coordinate.
         * \param w New w coordinate.
         */
        void set(float const x, float const y, float const z, float const w);

        /**
         * Change axis values by the given vector values
         *
         * \param v Vector to use as copy
         */
        void set(VectF4 const& v);


    // -------------------------------------------------------------------------
    // Static Functions
    // -------------------------------------------------------------------------
    public:
        /**
         * Get Dot Product of 2 vectors.
         *
         * \param v1 Vector 1
         * \param v2 Vector 2
         * \return The dot product v1.v2
         */
        static float dotProduct3(VectF4 const& v1, VectF4 const& v2);

        /**
         * Get Dot Product of 2 vectors using only axis X,Y,and Z (No W)
         *
         * \param v1 Vector 1
         * \param v2 Vector 2
         * \return The dot product v1.v2
         */
        static float dotProduct(VectF4 const& v1, VectF4 const& v2);


    // -------------------------------------------------------------------------
    // Operators overload
    // -------------------------------------------------------------------------
    public:
        // Comparison operators
        bool operator==(VectF4 const& v) const;
        bool operator!=(VectF4 const& v) const;

        // Arithmetic operators
        VectF4 operator*(float const s) const;
        VectF4 operator/(float const s) const;
        VectF4 operator+(VectF4 const& v) const;
        VectF4 operator-(VectF4 const& v) const;

        VectF4& operator*=(float const s);
        VectF4& operator/=(float const s);
        VectF4& operator+=(VectF4 const& v);
        VectF4& operator-=(VectF4 const& v);

        // Flux operators
        friend std::ostream& operator<<(std::ostream& os, VectF4 const& v);
};


// *********************** INLINES *********************************************


// -----------------------------------------------------------------------------
// Constructors
// -----------------------------------------------------------------------------
inline VectF4::VectF4(void) :x(0.0f), y(0.0f), z(0.0f), w(0.0f) {};

inline VectF4::VectF4(float x, float y, float z, float w) 
    : x(x),
      y(y),
      z(z),
      w(w) {
}


// -----------------------------------------------------------------------------
// Functions
// -----------------------------------------------------------------------------
inline float VectF4::length() const {
    return sqrt(this->squareLength());
}

inline float VectF4::length3() const {
    return sqrt(this->squareLength3());
}

inline float VectF4::squareLength() const {
    return (x*x) + (y*y) + (z*z) + (w*w);
}

inline float VectF4::squareLength3() const {
    return (x*x) + (y*y) + (z*z);
}

inline VectF4 VectF4::normalize() const {
    float l = this->length();
    VectF4 v(x/l, y/l, z/l, w/l);
    return v;
}

inline VectF4 VectF4::normalize3() const {
    float l = this->length3();
    VectF4 v(x/l, y/l, z/l, 0.0f);
    return v;
}


// -----------------------------------------------------------------------------
// Getters - Setters
// -----------------------------------------------------------------------------
inline void VectF4::set(float const x, float const y, float const z, float const w) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

inline void VectF4::set(VectF4 const& v) {
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
inline bool VectF4::operator==(VectF4 const& v) const{
    return  this->x == v.x &&
            this->y == v.y &&
            this->z == v.z &&
            this->w == v.w;
}

inline bool VectF4::operator!=(VectF4 const& v) const{
    return  this->x != v.x ||
            this->y != v.y ||
            this->z != v.z ||
            this->w != v.w;
}

inline VectF4 VectF4::operator*(float const s) const{
    return VectF4(x*s, y*s, z*s, w*s);
}

inline VectF4 VectF4::operator/(float const s) const{
    return VectF4(x/s, y/s, z/s, w/s);
}

inline VectF4 VectF4::operator+(VectF4 const& v) const{
    return VectF4(x+v.x, y+v.y, z+v.z, w+v.w);
}

inline VectF4 VectF4::operator-(VectF4 const& v) const{
    return VectF4(x-v.x, y-v.y, z-v.z, w-v.w);
}

inline VectF4& VectF4::operator*=(float const s){
    this->x = this->x * s;
    this->y = this->y * s;
    this->z = this->z * s;
    this->w = this->w * s;
    return *this;
}

inline VectF4& VectF4::operator/=(float const s){
    this->x = this->x / s;
    this->y = this->y / s;
    this->z = this->z / s;
    this->w = this->w / s;
    return *this;
}

inline VectF4& VectF4::operator+=(VectF4 const& v){
    this->x = this->x + v.x;
    this->y = this->y + v.y;
    this->z = this->z + v.z;
    this->w = this->w + v.w;
    return *this;
}

inline VectF4& VectF4::operator-=(VectF4 const& v){
    this->x = this->x - v.x;
    this->y = this->y - v.y;
    this->z = this->z - v.z;
    this->w = this->w - v.w;
    return *this;
}

inline std::ostream& operator<<(std::ostream &os, VectF4 const& v){
    os << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
    return os;
}


#endif



