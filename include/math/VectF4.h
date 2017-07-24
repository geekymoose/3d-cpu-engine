#ifndef ENGINE_MATH_VECTF4_H_
#define ENGINE_MATH_VECTF4_H_

// General includes
#include <iostream>
#include <cmath>
#ifdef __SSE4_1__
#   include <x86intrin.h>
#endif

// Project includes
#include "core/config.h"


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
#ifdef __SSE4_1__
        union{
            __m128 m128;
            struct{
                // To allow calling v.x / v.y / etc...
                // Warning: this assume float is 32, don't know a way to force it
                float x;
                float y;
                float z;
                float w;
            };
        };
#else
        float x;
        float y;
        float z;
        float w;
#endif

    // -------------------------------------------------------------------------
    // Constructors
    // -------------------------------------------------------------------------
    public:
        /**
         * Create a new null vector (All components to 0).
         */
        VectF4(void);

        /**
         * Create initialized vector.
         *
         * \param x The x value to set.
         * \param y The y value to set.
         * \param z The z value to set.
         * \param w The w value to set.
         */
        explicit VectF4(const float x, const float y, const float z, const float w);

        /**
         * Create initialized vector.
         * Each components are set with the given value.
         *
         * \param s Value to set for all components.
         */
        explicit VectF4(const float s);

#ifdef __SSE4_1__
        explicit VectF4(const __m128 v);
#endif


    // -------------------------------------------------------------------------
    // Functions
    // -------------------------------------------------------------------------
    public:
        /**
         * Gets the length of this vector.
         *
         * \return The length (Magnitude) of this vector.
         */
        float length() const;

        /**
         * Gets the length of this vector without W axis.
         *
         * \return The length (Magnitude) of this vector.
         */
        float length3() const;

        /**
         * Gets the square length of this vector.
         *
         *\return The square length (Magnitude) of this vector.
         */
        float squareLength() const;

        /**
         * Gets the square length of this vector without W axis.
         *
         *\return The square length (Magnitude) of this vector.
         */
        float squareLength3() const;

        /**
         * Returns a normalized copy of this vector.
         *
         * \warning
         * Function will crash if vector length() is zero!
         * Not verification is done for performance. (Hence 'fast')
         *
         * \return The new normalized vector.
         */
        VectF4 getNormalFast() const;

        /**
         * Returns a normalized copy of this vector without taking W axis into account.
         * W axis is set to 0.
         *
         * \warning
         * Function will crash if vector length3() is zero!
         * Not verification is done for performance. (Hence 'fast')
         *
         * \return The new normalized vector.
         */
        VectF4 getNormalFast3() const;

        /**
         * Normalize this vector in place.
         *
         * \warning
         * Function will crash if vector length() is zero!
         * Not verification is done for performance. (Hence 'fast')
         */
        void normalizeFast();

        /**
         * Gets Cross Product of this vector with another.
         * (a.k.a vector product or outer product).
         *
         * \note
         * Cross Product is only defined for 3 dimension.
         * W axis is skipped.
         *
         * \param v Vector to cross with.
         * \return The Vector cross product (this x other).
         */
        VectF4 getCrossProduct(VectF4 const& v) const;


    // -------------------------------------------------------------------------
    // Static Functions
    // -------------------------------------------------------------------------
    public:
        /**
         * Gets the Dot Product of 2 vectors.
         * (a.k.a scalar product or inner product).
         *
         * \param v1 Vector 1.
         * \param v2 Vector 2.
         * \return The dot product (v1.v2).
         */
        static float dotProduct(VectF4 const& v1, VectF4 const& v2);

        /**
         * Gets the Dot Product of 2 vectors using only axis X, Y, and Z (No W).
         * (a.k.a scalar product or inner product).
         *
         * \param v1 Vector 1.
         * \param v2 Vector 2.
         * \return The dot product (v1.v2).
         */
        static float dotProduct3(VectF4 const& v1, VectF4 const& v2);

        /**
         * Gets the Cross Product of 2 vectors.
         * (a.k.a vector product or outer product).
         *
         * \note
         * Cross Product is only defined for 3 dimension.
         * W axis is skipped.
         *
         * \param v1 Vector 1.
         * \param v2 Vector 2.
         * \return The Vector cross product (v1 x v2).
         */
        static VectF4 crossProduct(VectF4 const& v1, VectF4 const& v2);


    // -------------------------------------------------------------------------
    // Getters - Setters
    // -------------------------------------------------------------------------
    public:
        /**
         * Sets all axis values of this.
         *
         * \param x New x coordinate.
         * \param y New y coordinate.
         * \param z New z coordinate.
         * \param w New w coordinate.
         */
        void set(float const x, float const y, float const z, float const w);

        /**
         * Copy values of the given vector in this.
         *
         * \param v Vector to use as copy.
         */
        void set(VectF4 const& v);

#ifdef __SSE4_1__
        void set(const __m128 v);
#endif


    // -------------------------------------------------------------------------
    // Operators overload
    // -------------------------------------------------------------------------
    public:

        /**
         * Returns the multiplication of each this components by a scalar.
         *
         * \param s Scalar to apply.
         * \return The new Vector.
         */
        VectF4 operator*(float const s) const;

        /**
         * Returns the multiplication of this by another vector.
         *
         * \param v The other vector.
         * \return The new vector.
         */
        VectF4 operator*(VectF4 const& v) const;

        /**
         * Returns the division of each this components by a scalar.
         *
         * \warning
         * Function will crash if scalar is zero.
         *
         * \param v Vector to divide with.
         * \return New vector.
         */
        VectF4 operator/(float const s) const;

        /**
         * Returns the division of this components by another vector.
         *
         * \warning
         * Function will crash if other vector has a zero component.
         *
         * \param v The other vector.
         * \return The new vector.
         */
        VectF4 operator/(VectF4 const& v) const;

        /**
         * Returns the addition of each this components by a scalar.
         *
         * \param s Scalar.
         * \return New vector.
         */
        VectF4 operator+(float const s) const;

        /**
         * Returns a new vector addition of this vector with v.
         *
         * \param v The other vector.
         * \return New vector.
         */
        VectF4 operator+(VectF4 const& v) const;

        /**
         * Returns the subtraction of each this components by a scalar.
         *
         * \param s Scalar.
         * \return New vector.
         */
        VectF4 operator-(float const s) const;

        /**
         * Returns a new vector subtraction of this vector by v.
         *
         * \param v The other vector.
         * \return New vector.
         */
        VectF4 operator-(VectF4 const& v) const;

        /**
         * Multiplies this by a scalar.
         *
         * param s The scalar value.
         * \return Reference to the current vector after multiplication.
         */
        VectF4& operator*=(float const s);

        /**
         * Multiplies this by a vector.
         *
         * param v The other vector.
         * \return Reference to the current vector after calculation.
         */
        VectF4& operator*=(VectF4 const& v);

        /**
         * Divides this by a scalar.
         *
         * \warning
         * Function will crash if scalar is zero.
         *
         * param s The scalar value.
         * \return Reference to the current vector after division.
         */
        VectF4& operator/=(float const s);

        /**
         * Divides this by a vector.
         *
         * \warning
         * Function will crash if other vector has a zero component.
         *
         * param v The other vector.
         * \return Reference to the current vector after calculation.
         */
        VectF4& operator/=(VectF4 const& v);

        /**
         * Adds a vector to this.
         *
         * \param v The other vector.
         * \return Reference to the current vector after addition.
         */
        VectF4& operator+=(VectF4 const& v);

        /**
         * Adds a scalar to each this components.
         *
         * \param s Scalar value.
         * \return Reference to the current vector after addition.
         */
        VectF4& operator+=(float const s);

        /**
         * Subtracts a scalar to each this components.
         *
         * \param v Scalar value.
         * \return Reference to the current vector after subtraction.
         */
        VectF4& operator-=(float const s);

        /**
         * Subtracts a vector to this.
         *
         * \param v The other vector.
         * \return Reference to the current vector after subtraction.
         */
        VectF4& operator-=(VectF4 const& v);

        /**
         * Checks equality of 2 vectors.
         *
         * \param v The other vector.
         * \return True if both vectors have same component values, otherwise, return false.
         */
        bool operator==(VectF4 const& v) const;

        /**
         * Checks inequality of the 2 vectors.
         *
         * \param v The other vector.
         * \return True if not equal, otherwise, return false.
         */
        bool operator!=(VectF4 const& v) const;

        /**
         * Gets a copy of the component at requested position.
         *
         * \warning
         * Must be between 0 and 3 or program will crash.
         * For performance raison, no check is done.
         * \return Copy of component v[index].
         */
        float operator[](const size_t index) const;

        /**
         * Gets a reference to the  component at requested position.
         *
         * \warning
         * Must be between 0 and 3 or program will crash.
         * For performance raison, no check is done.
         * \return Reference to component v[index].
         */
        float& operator[](const size_t index);

        /**
         * Writes a simple string representation of the vector.
         *
         * \param os Stream where to write.
         * \param v Vector print.
         */
        friend std::ostream& operator<<(std::ostream& os, VectF4 const& v);
} GCC_ALIGNED(16);


#include "VectF4.inl"

#endif



