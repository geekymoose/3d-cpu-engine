#ifndef ENGINE_MATH_VECTF3_H_
#define ENGINE_MATH_VECTF3_H_

// General includes
#include <iostream>
#include <cmath>
#ifdef __SSE4_1__
    #include <x86intrin.h>
#endif

// Project includes
#include "core/config.h"


/**
 * 3 Dimensions vector with float precision.
 *
 * \author  Constantin MASSON
 */
class VectF3 {
    // -------------------------------------------------------------------------
    // Attributes
    // -------------------------------------------------------------------------
    public:
#ifdef __SSE4_1__
        union{
            __m128 m128; // Last element is unused
            struct{
                // To allow calling v.x / v.y / etc...
                // Warning: this assume float is 32, don't know a way to force it
                float x;
                float y;
                float z;
            };
        };
#else
        float x;
        float y;
        float z;
#endif


    // -------------------------------------------------------------------------
    // Constructors
    // -------------------------------------------------------------------------
    public:
        VectF3(void);
        explicit VectF3(float x, float y, float z);
#ifdef __SSE4_1__
        explicit VectF3(__m128 v); // Only for internal use
#endif



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
         * Get the square length of this vector.
         *
         *\return The square length (Magnitude) of this vector.
         */
        float squareLength() const;

        /**
         * Returns a normalized copy of this vector.
         * Vector shouldn't be null (No check done here).
         *
         * \return The normalized vector.
         */
        VectF3 normalize() const;

        /**
         * Get Cross Product of this vector with another.
         * (a.k.a vector product or outer product).
         *
         * \param v Vector to cross with
         * \return The Vector cross product (this x other).
         */
        VectF3 crossProduct(VectF3 const& v) const;


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
         */
        void set(float const x, float const y, float const z);

        /**
         * Change axis values by the given vector values.
         *
         * \param v Vector to use as copy.
         */
        void set(VectF3 const& v);


    // -------------------------------------------------------------------------
    // Static Functions
    // -------------------------------------------------------------------------
    public:
        /**
         * Get Dot Product of 2 vectors.
         * (a.k.a scalar product or inner product).
         *
         * \param v1 Vector 1.
         * \param v2 Vector 2.
         * \return The dot product (v1.v2).
         */
        static float dotProduct(VectF3 const& v1, VectF3 const& v2);


    // -------------------------------------------------------------------------
    // Operators overload
    // -------------------------------------------------------------------------
    public:
        // Comparison operators
        bool operator==(VectF3 const& v) const;
        bool operator!=(VectF3 const& v) const;

        // Arithmetic operators
        VectF3 operator*(float const s) const;
        VectF3 operator/(float const s) const;
        VectF3 operator+(VectF3 const& v) const;
        VectF3 operator-(VectF3 const& v) const;

        VectF3& operator*=(float const s);
        VectF3& operator/=(float const s);
        VectF3& operator+=(VectF3 const& v);
        VectF3& operator-=(VectF3 const& v);

        // Flux operators
        friend std::ostream& operator<<(std::ostream& os, VectF3 const& v);
} GCC_ALIGNED(16);


#include "VectF3.inl"

#endif



