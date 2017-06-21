// -----------------------------------------------------------------------------
// Unit Tests for VectF4 class
// GoogleTest Framework
//
// Author: Constantin Masson
// -----------------------------------------------------------------------------
#include <iostream>

#include "gtest/gtest.h"
#include "math/VectF4.h"


// ----------------------------------------------------------------------------
// MACRO
// ----------------------------------------------------------------------------
#define ASSERT_VECTF4_EQ(v1, v2) \
    ASSERT_FLOAT_EQ(v1.x, v2.x); \
    ASSERT_FLOAT_EQ(v1.y, v2.y); \
    ASSERT_FLOAT_EQ(v1.z, v2.z); \
    ASSERT_FLOAT_EQ(v1.w, v2.w)

#define ASSERT_VECTF4_VALUES_EQ(v1, X, Y, Z, W) \
    ASSERT_FLOAT_EQ(v1.x, X); \
    ASSERT_FLOAT_EQ(v1.y, Y); \
    ASSERT_FLOAT_EQ(v1.z, Z); \
    ASSERT_FLOAT_EQ(v1.w, W)


namespace {

// ----------------------------------------------------------------------------
// Fixture object to test VectF4
// ----------------------------------------------------------------------------
class VectF4Test : public ::testing::Test {
    protected:
        VectF4 v0;
        VectF4 v1;
        VectF4 v2;
        VectF4 v3;
    protected:
        VectF4Test()
            : v1(1.0f, 2.0f, 3.0f, 4.0f),
              v2(5.5f, 3.5f, -1.0f, 10.0f),
              v3(-10.0f, 2.1f, -2.1f, -2.8f){
        }
        virtual ~VectF4Test() {
        }
        virtual void SetUp() {
        }
        virtual void TearDown() {
        }
};


// -----------------------------------------------------------------------------
// VectF4 functions TESTS
// -----------------------------------------------------------------------------
TEST_F(VectF4Test, length) {
    ASSERT_FLOAT_EQ(v0.length(), 0);
    ASSERT_FLOAT_EQ(v1.length(), 5.4772256);
    ASSERT_FLOAT_EQ(v2.length(), 11.9791486);
    ASSERT_FLOAT_EQ(v3.length(), 10.8009259);
}

TEST_F(VectF4Test, length3) {
    ASSERT_FLOAT_EQ(v0.length3(), 0);
    ASSERT_FLOAT_EQ(v1.length3(), 3.7416574);
    ASSERT_FLOAT_EQ(v2.length3(), 6.595453);
    ASSERT_FLOAT_EQ(v3.length3(), 10.4316825);
}

TEST_F(VectF4Test, squareLength) {
    ASSERT_FLOAT_EQ(v0.squareLength(), 0);
    ASSERT_FLOAT_EQ(v1.squareLength(), 30);
    ASSERT_FLOAT_EQ(v2.squareLength(), 143.5);
    ASSERT_FLOAT_EQ(v3.squareLength(), 116.66);
}

TEST_F(VectF4Test, squareLength3) {
    ASSERT_FLOAT_EQ(v0.squareLength3(), 0);
    ASSERT_FLOAT_EQ(v1.squareLength3(), 14);
    ASSERT_FLOAT_EQ(v2.squareLength3(), 43.5);
    ASSERT_FLOAT_EQ(v3.squareLength3(), 108.82);
}

TEST_F(VectF4Test, normalize) {
    // v0 can't be normalized because div by 0 (Check on user responsibility)
    // v1 test
    VectF4 v = v1.normalize();
    ASSERT_VECTF4_VALUES_EQ(v, 0.1825742, 0.3651484, 0.5477226, 0.7302967);
    // v2 test
    v = v2.normalize();
    ASSERT_VECTF4_VALUES_EQ(v, 0.4591311, 0.2921744, -0.0834784, 0.8347839);
    // v3 test
    v = v3.normalize();
    ASSERT_VECTF4_VALUES_EQ(v, -0.9258466, 0.1944278, -0.1944278, -0.259237);
}

TEST_F(VectF4Test, normalize3) {
    // v1 test
    VectF4 v = v1.normalize3();
    ASSERT_VECTF4_VALUES_EQ(v, 0.2672612, 0.5345225, 0.8017837, 0);
    // v2 test
    v = v2.normalize3();
    ASSERT_VECTF4_VALUES_EQ(v, 0.8339078, 0.5306686, -0.1516196, 0);
    // v3 test
    v = v3.normalize3();
    ASSERT_VECTF4_VALUES_EQ(v, -0.9586181, 0.2013098, -0.2013098, 0);
}

TEST_F(VectF4Test, crossProduct3) {
    // v1
    VectF4 vt1 = v1.crossProduct3(v1);
    VectF4 vt2 = v1.crossProduct3(v2);
    VectF4 vt3 = v1.crossProduct3(v3);
    ASSERT_VECTF4_VALUES_EQ(vt1, 0,0,0,0);
    ASSERT_VECTF4_VALUES_EQ(vt2, -12.5, 17.5, -7.5, 0);
    ASSERT_VECTF4_VALUES_EQ(vt3, -10.5, -27.9, 22.1, 0);
    // v2
    vt1 = v2.crossProduct3(v1);
    vt2 = v2.crossProduct3(v2);
    vt3 = v2.crossProduct3(v3);
    ASSERT_VECTF4_VALUES_EQ(vt1, 12.5, -17.5, 7.5, 0);
    ASSERT_VECTF4_VALUES_EQ(vt2, 0,0,0,0);
    ASSERT_VECTF4_VALUES_EQ(vt3, -5.25, 21.55, 46.55, 0);
    // v3
    vt1 = v3.crossProduct3(v1);
    vt2 = v3.crossProduct3(v2);
    vt3 = v3.crossProduct3(v3);
    ASSERT_VECTF4_VALUES_EQ(vt1, 10.5, 27.9, -22.1, 0);
    ASSERT_VECTF4_VALUES_EQ(vt2, 5.25, -21.55, -46.55, 0);
    ASSERT_VECTF4_VALUES_EQ(vt3, 0,0,0,0);
}


// -----------------------------------------------------------------------------
// VectF4 static functions TESTS
// -----------------------------------------------------------------------------
TEST_F(VectF4Test, dotProduct) {
    // v1
    float vt1 = VectF4::dotProduct(v1, v1);
    float vt2 = VectF4::dotProduct(v1, v2);
    float vt3 = VectF4::dotProduct(v1, v3);
    ASSERT_FLOAT_EQ(vt1, 30);
    ASSERT_FLOAT_EQ(vt2, 49.5);
    ASSERT_FLOAT_EQ(vt3, -23.3);
    // v2
    vt1 = VectF4::dotProduct(v2, v1);
    vt2 = VectF4::dotProduct(v2, v2);
    vt3 = VectF4::dotProduct(v2, v3);
    ASSERT_FLOAT_EQ(vt1, 49.5);
    ASSERT_FLOAT_EQ(vt2, 143.5);
    ASSERT_FLOAT_EQ(vt3, -73.55);
    // v3
    vt1 = VectF4::dotProduct(v3, v1);
    vt2 = VectF4::dotProduct(v3, v2);
    vt3 = VectF4::dotProduct(v3, v3);
    ASSERT_FLOAT_EQ(vt1, -23.3);
    ASSERT_FLOAT_EQ(vt2, -73.55);
    ASSERT_FLOAT_EQ(vt3, 116.66);
}

TEST_F(VectF4Test, dotProduct3) {
    // v1
    float vt1 = VectF4::dotProduct3(v1, v1);
    float vt2 = VectF4::dotProduct3(v1, v2);
    float vt3 = VectF4::dotProduct3(v1, v3);
    ASSERT_FLOAT_EQ(vt1, 14);
    ASSERT_FLOAT_EQ(vt2, 9.5);
    ASSERT_FLOAT_EQ(vt3, -12.100000000000001);
    // v2
    vt1 = VectF4::dotProduct3(v2, v1);
    vt2 = VectF4::dotProduct3(v2, v2);
    vt3 = VectF4::dotProduct3(v2, v3);
    ASSERT_FLOAT_EQ(vt1, 9.5);
    ASSERT_FLOAT_EQ(vt2, 43.5);
    ASSERT_FLOAT_EQ(vt3, -45.55);
    // v3
    vt1 = VectF4::dotProduct3(v3, v1);
    vt2 = VectF4::dotProduct3(v3, v2);
    vt3 = VectF4::dotProduct3(v3, v3);
    ASSERT_FLOAT_EQ(vt1, -12.100000000000001);
    ASSERT_FLOAT_EQ(vt2, -45.55);
    ASSERT_FLOAT_EQ(vt3, 108.82);
}


// -----------------------------------------------------------------------------
// Operators overload TESTS
// -----------------------------------------------------------------------------
TEST_F(VectF4Test, equal) {
    ASSERT_TRUE(v0==v0);
    ASSERT_TRUE(v1==v1);
    ASSERT_TRUE(v2==v2);
    ASSERT_TRUE(v3==v3);
}

TEST_F(VectF4Test, notequal) {
    ASSERT_FALSE(v0!=v0);
    ASSERT_FALSE(v1!=v1);
    ASSERT_FALSE(v2!=v2);
    ASSERT_FALSE(v3!=v3);
    ASSERT_TRUE(v0!=v3);
    ASSERT_TRUE(v1!=v0);
    ASSERT_TRUE(v2!=v3);
    ASSERT_TRUE(v3!=v2);
}

TEST_F(VectF4Test, multiply) {
    // v0
    VectF4 vt1 = v0 * 13.3;
    VectF4 vt2 = v0 * -9.2;
    VectF4 vt3 = v0 * 4.9;
    ASSERT_VECTF4_VALUES_EQ(vt1, 0,0,0,0);
    ASSERT_VECTF4_VALUES_EQ(vt2, 0,0,0,0);
    ASSERT_VECTF4_VALUES_EQ(vt3, 0,0,0,0);
    // v1
    vt1 = v1 * 13.3;
    vt2 = v1 * -9.2;
    vt3 = v1 * 4.9;
    ASSERT_VECTF4_VALUES_EQ(vt1, 13.3, 26.6, 39.9, 53.2);
    ASSERT_VECTF4_VALUES_EQ(vt2, -9.2, -18.4, -27.6, -36.8);
    ASSERT_VECTF4_VALUES_EQ(vt3, 4.9, 9.8, 14.7, 19.6);
    // v2
    vt1 = v2 * 13.3;
    vt2 = v2 * -9.2;
    vt3 = v2 * 4.9;
    ASSERT_VECTF4_VALUES_EQ(vt1, 73.15, 46.55, -13.3, 133.0);
    ASSERT_VECTF4_VALUES_EQ(vt2, -50.6, -32.2, 9.2, -92.0);
    ASSERT_VECTF4_VALUES_EQ(vt3, 26.95, 17.15, -4.9, 49.0);
    // v3
    vt1 = v3 * 13.3;
    vt2 = v3 * -9.2;
    vt3 = v3 * 4.9;
    ASSERT_VECTF4_VALUES_EQ(vt1, -133.0, 27.93, -27.93, -37.24);
    ASSERT_VECTF4_VALUES_EQ(vt2, 92.0, -19.32, 19.32, 25.76);
    ASSERT_VECTF4_VALUES_EQ(vt3, -49.0, 10.29, -10.29, -13.72);
}

TEST_F(VectF4Test, divide) {
    // v0
    VectF4 vt1 = v0 / 13.3;
    VectF4 vt2 = v0 / -9.2;
    VectF4 vt3 = v0 / 4.9;
    ASSERT_VECTF4_VALUES_EQ(vt1, 0,0,0,0);
    ASSERT_VECTF4_VALUES_EQ(vt2, 0,0,0,0);
    ASSERT_VECTF4_VALUES_EQ(vt3, 0,0,0,0);
    // v1
    vt1 = v1 / 13.3;
    vt2 = v1 / -9.2;
    vt3 = v1 / 4.9;
    ASSERT_VECTF4_VALUES_EQ(vt1, 0.075187966, 0.1503759, 0.2255639, 0.3007519);
    ASSERT_VECTF4_VALUES_EQ(vt2, -0.10869566, -0.2173913, -0.326087, -0.4347826);
    ASSERT_VECTF4_VALUES_EQ(vt3, 0.2040816, 0.4081633, 0.6122449, 0.8163265);
    // v2
    vt1 = v2 / 13.3;
    vt2 = v2 / -9.2;
    vt3 = v2 / 4.9;
    ASSERT_VECTF4_VALUES_EQ(vt1, 0.4135338, 0.2631579, -0.075187966, 0.7518797);
    ASSERT_VECTF4_VALUES_EQ(vt2, -0.5978261, -0.3804348, 0.10869566, -1.0869565);
    ASSERT_VECTF4_VALUES_EQ(vt3, 1.122449, 0.7142857, -0.2040816, 2.0408163);
    // v3
    vt1 = v3 / 13.3;
    vt2 = v3 / -9.2;
    vt3 = v3 / 4.9;
    ASSERT_VECTF4_VALUES_EQ(vt1, -0.7518797, 0.1578947, -0.1578947, -0.2105263);
    ASSERT_VECTF4_VALUES_EQ(vt2, 1.0869565, -0.2282609, 0.2282609, 0.3043478);
    ASSERT_VECTF4_VALUES_EQ(vt3, -2.0408163, 0.4285714, -0.4285714, -0.5714286);
}

TEST_F(VectF4Test, add) {
    // v1
    VectF4 vt1 = v1 + v1;
    VectF4 vt2 = v1 + v2;
    VectF4 vt3 = v1 + v3;
    ASSERT_VECTF4_VALUES_EQ(vt1, 2, 4, 6, 8);
    ASSERT_VECTF4_VALUES_EQ(vt2, 6.5, 5.5, 2, 14);
    ASSERT_VECTF4_VALUES_EQ(vt3, -9, 4.1, 0.9, 1.2);
    // v2
    vt1 = v2 + v1;
    vt2 = v2 + v2;
    vt3 = v2 + v3;
    ASSERT_VECTF4_VALUES_EQ(vt1, 6.5, 5.5, 2, 14);
    ASSERT_VECTF4_VALUES_EQ(vt2, 11.0, 7.0, -2, 20);
    ASSERT_VECTF4_VALUES_EQ(vt3, -4.5, 5.6, -3.1, 7.2);
    // v3
    vt1 = v3 + v1;
    vt2 = v3 + v2;
    vt3 = v3 + v3;
    ASSERT_VECTF4_VALUES_EQ(vt1, -9, 4.1, 0.9, 1.2);
    ASSERT_VECTF4_VALUES_EQ(vt2, -4.5, 5.6, -3.1, 7.2);
    ASSERT_VECTF4_VALUES_EQ(vt3, -20, 4.2, -4.2, -5.6);
}

TEST_F(VectF4Test, substract) {
    // v1
    VectF4 vt1 = v1 - v1;
    VectF4 vt2 = v1 - v2;
    VectF4 vt3 = v1 - v3;
    ASSERT_VECTF4_VALUES_EQ(vt1, 0,0,0,0);
    ASSERT_VECTF4_VALUES_EQ(vt2, -4.5, -1.5, 4, -6);
    ASSERT_VECTF4_VALUES_EQ(vt3, 11, -0.099999905, 5.1, 6.8);
    // v2
    vt1 = v2 - v1;
    vt2 = v2 - v2;
    vt3 = v2 - v3;
    ASSERT_VECTF4_VALUES_EQ(vt1, 4.5, 1.5, -4, 6);
    ASSERT_VECTF4_VALUES_EQ(vt2, 0,0,0,0);
    ASSERT_VECTF4_VALUES_EQ(vt3, 15.5, 1.4, 1.1, 12.8);
    // v3
    vt1 = v3 - v1;
    vt2 = v3 - v2;
    vt3 = v3 - v3;
    ASSERT_VECTF4_VALUES_EQ(vt1, -11, 0.099999905, -5.1, -6.8);
    ASSERT_VECTF4_VALUES_EQ(vt2, -15.5, -1.4, -1.1, -12.8);
    ASSERT_VECTF4_VALUES_EQ(vt3, 0,0,0,0);
}


// -----------------------------------------------------------------------------
// Operators overload TESTS (Others)
// -----------------------------------------------------------------------------

TEST_F(VectF4Test, multiplyinplace) {
    v0 *= 13.3;
    v1 *= -9.2;
    v2 *= 4.9;
    v3 *= 13.3;
    ASSERT_VECTF4_VALUES_EQ(v0, 0,0,0,0);
    ASSERT_VECTF4_VALUES_EQ(v1, -9.2, -18.4, -27.6, -36.8);
    ASSERT_VECTF4_VALUES_EQ(v2, 26.95, 17.15, -4.9, 49.0);
    ASSERT_VECTF4_VALUES_EQ(v3, -133.0, 27.93, -27.93, -37.24);
}

TEST_F(VectF4Test, divideinplace) {
    v0 /= 13.3;
    v1 /= -9.2;
    v2 /= 13.3;
    v3 /= 4.9;
    ASSERT_VECTF4_VALUES_EQ(v0, 0,0,0,0);
    ASSERT_VECTF4_VALUES_EQ(v1, -0.10869566, -0.2173913, -0.326087, -0.4347826);
    ASSERT_VECTF4_VALUES_EQ(v2, 0.4135338, 0.2631579, -0.075187966, 0.7518797);
    ASSERT_VECTF4_VALUES_EQ(v3, -2.0408163, 0.4285714, -0.4285714, -0.5714286);
}

TEST_F(VectF4Test, addinplace) {
    v1 += v1;
    v2 += v3;
    ASSERT_VECTF4_VALUES_EQ(v1, 2, 4, 6, 8);
    ASSERT_VECTF4_VALUES_EQ(v2, -4.5, 5.6, -3.1, 7.2);
}

TEST_F(VectF4Test, substractinplace) {
    v2 -= v1;
    v3 -= v3;
    ASSERT_VECTF4_VALUES_EQ(v2, 4.5, 1.5, -4, 6);
    ASSERT_VECTF4_VALUES_EQ(v3, 0,0,0,0);
}


} // End namespace


