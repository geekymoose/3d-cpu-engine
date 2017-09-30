#pragma once

#include <iostream>
#include <cmath>

#include "core/config.h"


/**
 * 2 Dimensions vector with floating point precision.
 *
 * \since   Aug 4, 2017
 * \author  Constantin MASSON
 */
class VectF2 {
    // -------------------------------------------------------------------------
    // Attributes
    // -------------------------------------------------------------------------
    public:
        float x;
        float y;

    // -------------------------------------------------------------------------
    // Constructors
    // -------------------------------------------------------------------------
    public:
        /**
         * Create a new null vector (All components to 0).
         */
        VectF2();

        /**
         * Create initialized vector.
         *
         * \param x The x value to set.
         * \param y The y value to set.
         */
        explicit VectF2(const float x, const float y);

        /**
         * Create initialized vector.
         * Each components are set with the given value.
         *
         * \param s Value to set for all components.
         */
        explicit VectF2(const float s);


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
         * Gets the square length of this vector.
         *
         * \return The square length (Magnitude) of this vector.
         */
        float squareLength() const;

        /**
         * Returns a normalized copy of this vector.
         *
         * \warning
         * If vector length is zero, a division by zero appears.
         * Since floating point division by 0, vector is filled with 'infinite'.
         * Not verification is done for performance. (Hence 'fast')
         *
         * \return The new normalized vector.
         */
        VectF2 getNormalFast() const;

        /**
         * Normalize this vector in place.
         *
         * \warning
         * If vector length is zero, a division by zero appears.
         * Since floating point division by 0, vector is filled with 'infinite'.
         * Not verification is done for performance. (Hence 'fast')
         */
        void normalizeFast();


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
        static float dotProduct(VectF2 const& v1, VectF2 const& v2);


    // -------------------------------------------------------------------------
    // Getters - Setters
    // -------------------------------------------------------------------------
    public:
        /**
         * Sets all axis values of this.
         *
         * \param x New x coordinate.
         * \param y New y coordinate.
         */
        void set(float const x, float const y);

        /**
         * Copy values of the given vector in this.
         *
         * \param v Vector to use as copy.
         */
        void set(VectF2 const& v);


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
        VectF2 operator*(float const s) const;

        /**
         * Returns the multiplication of this by another vector.
         *
         * \param v The other vector.
         * \return The new vector.
         */
        VectF2 operator*(VectF2 const& v) const;

        /**
         * Returns the division of each this components by a scalar.
         *
         * \warning
         * If scalar is zero, a division by zero appears.
         * Since floating point division by 0, vector is filled with 'infinite'.
         * Not verification is done for performance. (Hence 'fast')
         *
         * \param v Vector to divide with.
         * \return New vector.
         */
        VectF2 operator/(float const s) const;

        /**
         * Returns the division of this components by another vector.
         *
         * \warning
         * If other vector has a zero component, a division by zero appears.
         * Since floating point division by 0, vector is filled with 'infinite'.
         * Not verification is done for performance. (Hence 'fast')
         *
         * \param v The other vector.
         * \return The new vector.
         */
        VectF2 operator/(VectF2 const& v) const;

        /**
         * Returns the addition of each this components by a scalar.
         *
         * \param s Scalar.
         * \return New vector.
         */
        VectF2 operator+(float const s) const;

        /**
         * Returns a new vector addition of this vector with v.
         *
         * \param v The other vector.
         * \return New vector.
         */
        VectF2 operator+(VectF2 const& v) const;

        /**
         * Returns the subtraction of each this components by a scalar.
         *
         * \param s Scalar.
         * \return New vector.
         */
        VectF2 operator-(float const s) const;

        /**
         * Returns a new vector subtraction of this vector by v.
         *
         * \param v The other vector.
         * \return New vector.
         */
        VectF2 operator-(VectF2 const& v) const;

        /**
         * Multiplies this by a scalar.
         *
         * param s The scalar value.
         * \return Reference to the current vector after multiplication.
         */
        VectF2& operator*=(float const s);

        /**
         * Multiplies this by a vector.
         *
         * param v The other vector.
         * \return Reference to the current vector after calculation.
         */
        VectF2& operator*=(VectF2 const& v);

        /**
         * Divides this by a scalar.
         *
         * \warning
         * If scalar is zero, a division by zero appears.
         * Since floating point division by 0, vector is filled with 'infinite'.
         * Not verification is done for performance. (Hence 'fast')
         *
         * param s The scalar value.
         * \return Reference to the current vector after division.
         */
        VectF2& operator/=(float const s);

        /**
         * Divides this by a vector.
         *
         * \warning
         * If other vector has a zero component, a division by zero appears.
         * Since floating point division by 0, vector is filled with 'infinite'.
         * Not verification is done for performance. (Hence 'fast')
         *
         * param v The other vector.
         * \return Reference to the current vector after calculation.
         */
        VectF2& operator/=(VectF2 const& v);

        /**
         * Adds a vector to this.
         *
         * \param v The other vector.
         * \return Reference to the current vector after addition.
         */
        VectF2& operator+=(VectF2 const& v);

        /**
         * Adds a scalar to each this components.
         *
         * \param s Scalar value.
         * \return Reference to the current vector after addition.
         */
        VectF2& operator+=(float const s);

        /**
         * Subtracts a scalar to each this components.
         *
         * \param v Scalar value.
         * \return Reference to the current vector after subtraction.
         */
        VectF2& operator-=(float const s);

        /**
         * Subtracts a vector to this.
         *
         * \param v The other vector.
         * \return Reference to the current vector after subtraction.
         */
        VectF2& operator-=(VectF2 const& v);

        /**
         * Checks equality of 2 vectors.
         *
         * \param v The other vector.
         * \return True if both vectors have same component values, otherwise, return false.
         */
        bool operator==(VectF2 const& v) const;

        /**
         * Checks inequality of the 2 vectors.
         *
         * \param v The other vector.
         * \return True if not equal, otherwise, return false.
         */
        bool operator!=(VectF2 const& v) const;

        /**
         * Gets a copy of the component at requested position.
         *
         * \warning
         * Index must be in range, otherwise this function will crash.
         * For performance raison, no check is done.
         *
         * \return Copy of component v[index].
         */
        float operator[](const size_t index) const;

        /**
         * Gets a reference to the  component at requested position.
         *
         * \warning
         * Index must be in range, otherwise this function will crash.
         * For performance raison, no check is done.
         *
         * \return Reference to component v[index].
         */
        float& operator[](const size_t index);

        /**
         * Writes a simple string representation of the vector.
         *
         * \param os Stream where to write.
         * \param v Vector print.
         */
        friend std::ostream& operator<<(std::ostream& os, VectF2 const& v);
};


#include "VectF2.inl"

