// -----------------------------------------------------------------------------
// Unit Tests for VectF2 class
// GoogleTest Framework
// -----------------------------------------------------------------------------
#include <iostream>

#include "gtest/gtest.h"
#include "math/VectF2.h"


// ----------------------------------------------------------------------------
// MACRO
// ----------------------------------------------------------------------------
#define ASSERT_VECTF2_EQ(v1, v2) \
    ASSERT_FLOAT_EQ(v1.x, v2.x); \
    ASSERT_FLOAT_EQ(v1.y, v2.y)

#define ASSERT_VECTF2_VALUES_EQ(vect, X, Y) \
    ASSERT_FLOAT_EQ(vect.x, X); \
    ASSERT_FLOAT_EQ(vect.y, Y)


namespace {

// ----------------------------------------------------------------------------
// Fixture object to test VectF2
// ----------------------------------------------------------------------------
class VectF2Test : public ::testing::Test {
    protected:
        VectF2 v0;
        VectF2 v1;
        VectF2 v2;
        VectF2 v3;
    protected:
        VectF2Test()
            : v1(1.0f, 2.0f),
              v2(5.5f, 3.5f),
              v3(-10.0f, 2.1f){
        }
        virtual ~VectF2Test() {}
        virtual void SetUp() {}
        virtual void TearDown() {}
};


// -----------------------------------------------------------------------------
// Constructors / Setters
// -----------------------------------------------------------------------------
TEST_F(VectF2Test, constructors) {
    VectF2 vec0;
    ASSERT_VECTF2_VALUES_EQ(vec0, 0.0f, 0.0f);
    VectF2 vec1(42.0f);
    ASSERT_VECTF2_VALUES_EQ(vec1, 42.0f, 42.0f);
    VectF2 vec2(-32.0f, 89.0f);
    ASSERT_VECTF2_VALUES_EQ(vec2, -32.0f, 89.0f);
}

TEST_F(VectF2Test, setters) {
    v0.set(4, -3);
    ASSERT_VECTF2_VALUES_EQ(v0, 4, -3);
    v0.set(v1);
    ASSERT_VECTF2_VALUES_EQ(v0, 1, 2);
}

TEST_F(VectF2Test, attributes) {
    ASSERT_TRUE(v0.x == 0);
    ASSERT_TRUE(v0.y == 0);
    ASSERT_TRUE(v1.x == 1.0f);
    ASSERT_TRUE(v1.y == 2.0f);
}


// -----------------------------------------------------------------------------
// Class Functions
// -----------------------------------------------------------------------------
TEST_F(VectF2Test, length) {
    ASSERT_FLOAT_EQ(v0.length(), 0.0f);
    ASSERT_FLOAT_EQ(v1.length(), 2.236067);
    ASSERT_FLOAT_EQ(v2.length(), 6.519202);
    ASSERT_FLOAT_EQ(v3.length(), 10.218121);
}

TEST_F(VectF2Test, squareLength) {
    ASSERT_FLOAT_EQ(v0.squareLength(), 0);
    ASSERT_FLOAT_EQ(v1.squareLength(), 5);
    ASSERT_FLOAT_EQ(v2.squareLength(), 42.5);
    ASSERT_FLOAT_EQ(v3.squareLength(), 104.41);
}

TEST_F(VectF2Test, getNormalFast) {
    ASSERT_VECTF2_VALUES_EQ(v1.getNormalFast(), 0.4472135, 0.8944271);
    ASSERT_VECTF2_VALUES_EQ(v2.getNormalFast(), 0.8436614, 0.5368754);
    ASSERT_VECTF2_VALUES_EQ(v3.getNormalFast(), -0.9786534, 0.2055172);
}

TEST_F(VectF2Test, normalizeFast) {
    v1.normalizeFast();
    v2.normalizeFast();
    v3.normalizeFast();
    ASSERT_VECTF2_VALUES_EQ(v1, 0.4472135, 0.8944271);
    ASSERT_VECTF2_VALUES_EQ(v2, 0.8436614, 0.5368754);
    ASSERT_VECTF2_VALUES_EQ(v3, -0.9786534, 0.2055172);
}


// -----------------------------------------------------------------------------
// Static functions
// -----------------------------------------------------------------------------
TEST_F(VectF2Test, dotProduct) {
    // v1
    ASSERT_FLOAT_EQ(VectF2::dotProduct(v1, v1), 5);
    ASSERT_FLOAT_EQ(VectF2::dotProduct(v1, v2), 12.5);
    ASSERT_FLOAT_EQ(VectF2::dotProduct(v1, v3), -5.8);
    // v2
    ASSERT_FLOAT_EQ(VectF2::dotProduct(v2, v1), 12.5);
    ASSERT_FLOAT_EQ(VectF2::dotProduct(v2, v2), 42.5);
    ASSERT_FLOAT_EQ(VectF2::dotProduct(v2, v3), -47.65);
    // v3
    ASSERT_FLOAT_EQ(VectF2::dotProduct(v3, v1), -5.8);
    ASSERT_FLOAT_EQ(VectF2::dotProduct(v3, v2), -47.65);
    ASSERT_FLOAT_EQ(VectF2::dotProduct(v3, v3), 104.41);
}


// -----------------------------------------------------------------------------
// Operators overload
// -----------------------------------------------------------------------------
TEST_F(VectF2Test, multiply_scalar) {
    float s1 = 13.3;
    float s2 = -9.2;
    float s3 = 4.9;
    // v0
    ASSERT_VECTF2_VALUES_EQ((v0 * s1), 0,0);
    ASSERT_VECTF2_VALUES_EQ((v0 * s2), 0,0);
    ASSERT_VECTF2_VALUES_EQ((v0 * s3), 0,0);
    // v1
    ASSERT_VECTF2_VALUES_EQ((v1 * s1), 13.3, 26.6);
    ASSERT_VECTF2_VALUES_EQ((v1 * s2), -9.2, -18.4);
    ASSERT_VECTF2_VALUES_EQ((v1 * s3), 4.9, 9.8);
    // v2
    ASSERT_VECTF2_VALUES_EQ((v2 * s1), 73.15, 46.55);
    ASSERT_VECTF2_VALUES_EQ((v2 * s2), -50.6, -32.2);
    ASSERT_VECTF2_VALUES_EQ((v2 * s3), 26.95, 17.15);
    // v3
    ASSERT_VECTF2_VALUES_EQ((v3 * s1), -133.0, 27.93);
    ASSERT_VECTF2_VALUES_EQ((v3 * s2), 92.0, -19.32);
    ASSERT_VECTF2_VALUES_EQ((v3 * s3), -49.0, 10.29);
}

TEST_F(VectF2Test, multiply_vector) {
    ASSERT_VECTF2_VALUES_EQ((v1 * v1), 1, 4);
    ASSERT_VECTF2_VALUES_EQ((v1 * v2), 5.5, 7);
}

TEST_F(VectF2Test, divide_scalar) {
    float s1 = 13.3;
    float s2 = -9.2;
    float s3 = 4.9;
    // v0
    ASSERT_VECTF2_VALUES_EQ((v0 / s1), 0,0);
    ASSERT_VECTF2_VALUES_EQ((v0 / s2), 0,0);
    ASSERT_VECTF2_VALUES_EQ((v0 / s3), 0,0);
    // v1
    ASSERT_VECTF2_VALUES_EQ((v1 / s1), 0.075187966, 0.1503759);
    ASSERT_VECTF2_VALUES_EQ((v1 / s2), -0.10869566, -0.2173913);
    ASSERT_VECTF2_VALUES_EQ((v1 / s3), 0.2040816, 0.4081633);
    // v2
    ASSERT_VECTF2_VALUES_EQ((v2 / s1), 0.4135338, 0.2631579);
    ASSERT_VECTF2_VALUES_EQ((v2 / s2), -0.5978261, -0.3804348);
    ASSERT_VECTF2_VALUES_EQ((v2 / s3), 1.122449, 0.7142857);
    // v3
    ASSERT_VECTF2_VALUES_EQ((v3 / s1), -0.7518797, 0.1578947);
    ASSERT_VECTF2_VALUES_EQ((v3 / s2), 1.0869565, -0.2282609);
    ASSERT_VECTF2_VALUES_EQ((v3 / s3), -2.0408163, 0.4285714);
}

TEST_F(VectF2Test, divide_vector) {
    ASSERT_VECTF2_VALUES_EQ((v0 / v2), 0, 0);
    ASSERT_VECTF2_VALUES_EQ((v1 / v1), 1, 1);
}

TEST_F(VectF2Test, add_scalar) {
    ASSERT_VECTF2_VALUES_EQ((v0 + 10), 10, 10);
    ASSERT_VECTF2_VALUES_EQ((v1 + 3.9), 4.9, 5.9);
    ASSERT_VECTF2_EQ((v3 + 0), v3);
}

TEST_F(VectF2Test, add_vector) {
    // v1
    ASSERT_VECTF2_VALUES_EQ((v1 + v1), 2, 4);
    ASSERT_VECTF2_VALUES_EQ((v1 + v2), 6.5, 5.5);
    ASSERT_VECTF2_VALUES_EQ((v1 + v3), -9, 4.1);
    // v2
    ASSERT_VECTF2_VALUES_EQ((v2 + v1), 6.5, 5.5);
    ASSERT_VECTF2_VALUES_EQ((v2 + v2), 11.0, 7.0);
    ASSERT_VECTF2_VALUES_EQ((v2 + v3), -4.5, 5.6);
    // v3
    ASSERT_VECTF2_VALUES_EQ((v3 + v1), -9, 4.1);
    ASSERT_VECTF2_VALUES_EQ((v3 + v2), -4.5, 5.6);
    ASSERT_VECTF2_VALUES_EQ((v3 + v3), -20, 4.2);
}

TEST_F(VectF2Test, substract_scalar) {
    ASSERT_VECTF2_VALUES_EQ((v0 - 10), -10, -10);
    ASSERT_VECTF2_VALUES_EQ((v2 - 2.5), 3, 1);
    ASSERT_VECTF2_EQ((v3 - 0), v3);
}

TEST_F(VectF2Test, substract_vector) {
    // v1
    ASSERT_VECTF2_VALUES_EQ((v1 - v1), 0,0);
    ASSERT_VECTF2_VALUES_EQ((v1 - v2), -4.5, -1.5);
    ASSERT_VECTF2_VALUES_EQ((v1 - v3), 11, -0.099999905);
    // v2
    ASSERT_VECTF2_VALUES_EQ((v2 - v1), 4.5, 1.5);
    ASSERT_VECTF2_VALUES_EQ((v2 - v2), 0,0);
    ASSERT_VECTF2_VALUES_EQ((v2 - v3), 15.5, 1.4);
    // v3
    ASSERT_VECTF2_VALUES_EQ((v3 - v1), -11, 0.099999905);
    ASSERT_VECTF2_VALUES_EQ((v3 - v2), -15.5, -1.4);
    ASSERT_VECTF2_VALUES_EQ((v3 - v3), 0,0);
}


// -----------------------------------------------------------------------------
// Operators overload (Inplace)
// -----------------------------------------------------------------------------
TEST_F(VectF2Test, multiplyin_scalar_place) {
    v0 *= 13.3;
    v1 *= -9.2;
    v2 *= 4.9;
    v3 *= 13.3;
    ASSERT_VECTF2_VALUES_EQ(v0, 0,0);
    ASSERT_VECTF2_VALUES_EQ(v1, -9.2, -18.4);
    ASSERT_VECTF2_VALUES_EQ(v2, 26.95, 17.15);
    ASSERT_VECTF2_VALUES_EQ(v3, -133.0, 27.93);
}

TEST_F(VectF2Test, multiply_vector_inplace) {
    v0 *= v3;
    v1 *= v2;
    ASSERT_VECTF2_VALUES_EQ(v0, 0, 0);
    ASSERT_VECTF2_VALUES_EQ(v1, 5.5, 7);
}

TEST_F(VectF2Test, divide_scalar_inplace) {
    v0 /= 13.3;
    v1 /= -9.2;
    v2 /= 13.3;
    v3 /= 4.9;
    ASSERT_VECTF2_VALUES_EQ(v0, 0,0);
    ASSERT_VECTF2_VALUES_EQ(v1, -0.10869566, -0.2173913);
    ASSERT_VECTF2_VALUES_EQ(v2, 0.4135338, 0.2631579);
    ASSERT_VECTF2_VALUES_EQ(v3, -2.0408163, 0.4285714);
}

TEST_F(VectF2Test, divide_vector_inplace) {
    v0 /= v3;
    v1 /= v1;
    ASSERT_VECTF2_VALUES_EQ(v0, 0, 0);
    ASSERT_VECTF2_VALUES_EQ(v1, 1, 1);
}

TEST_F(VectF2Test, add_scalar_inplace) {
    v0 += 2.4;
    v2 += 0;
    ASSERT_VECTF2_VALUES_EQ(v0, 2.4, 2.4);
    ASSERT_VECTF2_VALUES_EQ(v2, 5.5, 3.5);
}

TEST_F(VectF2Test, add_vector_inplace) {
    v1 += v1;
    v2 += v3;
    ASSERT_VECTF2_VALUES_EQ(v1, 2, 4);
    ASSERT_VECTF2_VALUES_EQ(v2, -4.5, 5.6);
}

TEST_F(VectF2Test, subtract_scalar_inplace) {
    v0 -= -922.32;
    v1 -= v1;
    v3 -= 0;
    ASSERT_VECTF2_VALUES_EQ(v0, 922.32, 922.32);
    ASSERT_VECTF2_VALUES_EQ(v1, 0, 0);
    ASSERT_VECTF2_VALUES_EQ(v3, -10, 2.1);
}

TEST_F(VectF2Test, substract_vector_inplace) {
    v2 -= v1;
    v3 -= v3;
    ASSERT_VECTF2_VALUES_EQ(v2, 4.5, 1.5);
    ASSERT_VECTF2_VALUES_EQ(v3, 0,0);
}


// -----------------------------------------------------------------------------
// Operators overload (Other)
// -----------------------------------------------------------------------------
TEST_F(VectF2Test, equal) {
    ASSERT_TRUE(v0==v0);
    ASSERT_TRUE(v1==v1);
    ASSERT_TRUE(v2==v2);
    ASSERT_TRUE(v3==v3);
}

TEST_F(VectF2Test, notequal) {
    ASSERT_FALSE(v0!=v0);
    ASSERT_FALSE(v1!=v1);
    ASSERT_FALSE(v2!=v2);
    ASSERT_FALSE(v3!=v3);
    ASSERT_TRUE(v0!=v3);
    ASSERT_TRUE(v1!=v0);
    ASSERT_TRUE(v2!=v3);
    ASSERT_TRUE(v3!=v2);
}

TEST_F(VectF2Test, access_operator) {
    ASSERT_EQ(v0[1], 0);
    ASSERT_EQ(v1[0], 1);
    ASSERT_EQ(v1[1], 2);
    ASSERT_EQ(v3[0], -10.0f);
}


} // End namespace



