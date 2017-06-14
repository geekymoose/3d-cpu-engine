#ifndef ENGINE_MATHS_VECT4_H_
#define ENGINE_MATHS_VECT4_H_

#include <iostream>
#include <cmath>

/**
 * 4 Dimensions vector with float precision
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
        VectF4();
        VectF4(float x, float y, float z, float w);
        VectF4(VectF4 const& v);

    // -------------------------------------------------------------------------
    // Functions
    // -------------------------------------------------------------------------
    public:
        float length() const;
        float squareLength() const;
        void normalize();
        VectF4 getUnitVect() const;
        void set(float const x, float const y, float const z, float const w);
        void set(VectF4 const& v);

    // -------------------------------------------------------------------------
    // Operators overload
    // -------------------------------------------------------------------------
    public:
        // Comparison operators
        bool operator==(VectF4 const& v);
        bool operator!=(VectF4 const& v);

    public:
        // Arithmetic operators
        VectF4 operator*(float const s);
        VectF4 operator/(float const s);
        VectF4 operator+(VectF4 const& v);
        VectF4 operator-(VectF4 const& v);

        VectF4& operator*=(float const s);
        VectF4& operator/=(float const s);
        VectF4& operator+=(VectF4 const& v);
        VectF4& operator-=(VectF4 const& v);
};

#endif



