// -----------------------------------------------------------------------------
// Unit Tests for MatrixF4 class
// GoogleTest Framework
//
// Author: Constantin Masson
// -----------------------------------------------------------------------------
#include <iostream>

#include "gtest/gtest.h"
#include "math/MatrixF4.h"


// ----------------------------------------------------------------------------
// MACRO
// ----------------------------------------------------------------------------
#define ASSERT_MATRIXF4_EQ(matrix, \
                           m11,m12,m13,m14, \
                           m21,m22,m23,m24, \
                           m31,m32,m33,m34, \
                           m41,m42,m43,m44) \
    ASSERT_FLOAT_EQ(matrix._m[0][0], m11); \
    ASSERT_FLOAT_EQ(matrix._m[0][1], m12); \
    ASSERT_FLOAT_EQ(matrix._m[0][2], m13); \
    ASSERT_FLOAT_EQ(matrix._m[0][3], m14); \
    \
    ASSERT_FLOAT_EQ(matrix._m[1][0], m21); \
    ASSERT_FLOAT_EQ(matrix._m[1][1], m22); \
    ASSERT_FLOAT_EQ(matrix._m[1][2], m23); \
    ASSERT_FLOAT_EQ(matrix._m[1][3], m24); \
    \
    ASSERT_FLOAT_EQ(matrix._m[2][0], m31); \
    ASSERT_FLOAT_EQ(matrix._m[2][1], m32); \
    ASSERT_FLOAT_EQ(matrix._m[2][2], m33); \
    ASSERT_FLOAT_EQ(matrix._m[2][3], m34); \
    \
    ASSERT_FLOAT_EQ(matrix._m[3][0], m41); \
    ASSERT_FLOAT_EQ(matrix._m[3][1], m42); \
    ASSERT_FLOAT_EQ(matrix._m[3][2], m43); \
    ASSERT_FLOAT_EQ(matrix._m[3][3], m44)

#define ASSERT_VECTF4_VALUES_EQ(vect, X, Y, Z, W) \
    ASSERT_FLOAT_EQ(vect.x, X); \
    ASSERT_FLOAT_EQ(vect.y, Y); \
    ASSERT_FLOAT_EQ(vect.z, Z); \
    ASSERT_FLOAT_EQ(vect.w, W)


namespace {

// ----------------------------------------------------------------------------
// Fixture object to test Matrix
// ----------------------------------------------------------------------------
class MatrixF4Test : public ::testing::Test {
    protected:
        MatrixF4 m1;
        MatrixF4 m2;
        MatrixF4 m3;
    protected:
        MatrixF4Test()
            : m1(
                VectF4(1,1,1,1),
                VectF4(1,1,1,1),
                VectF4(1,1,1,1),
                VectF4(1,1,1,1)),
              m2(
                VectF4(1,       42,     5,      0),
                VectF4(-2,      6,      -12,    0),
                VectF4(-2,      9,      14.5,   0),
                VectF4(-42,     42,     0,      1)),
              m3(
                VectF4(1,       2,      3,      4),
                VectF4(-1,      -2.5,   -3.2,   -4),
                VectF4(-22.5,   8.5,   32,     -1.5),
                VectF4(0,       0,      0,      1)) {
        }
        virtual void SetUp() {}
        virtual void TearDown() {}
};


// -----------------------------------------------------------------------------
// TESTS - Constructors
// -----------------------------------------------------------------------------
TEST_F(MatrixF4Test, constructor) {
    MatrixF4 mm1(1,2,3,4 ,5,6,7,8, 0,0,1,1, 1,1,5,5);
    MatrixF4 mm2(VectF4(1,2,3,4), VectF4(5,6,7,8), VectF4(0,0,1,1), VectF4(1,1,5,5));
    ASSERT_MATRIXF4_EQ(mm1, 1,2,3,4 ,5,6,7,8, 0,0,1,1, 1,1,5,5);
    ASSERT_MATRIXF4_EQ(mm2, 1,2,3,4 ,5,6,7,8, 0,0,1,1, 1,1,5,5);
}


// -----------------------------------------------------------------------------
// TESTS - General functions
// -----------------------------------------------------------------------------
TEST_F(MatrixF4Test, transposition) {
    ASSERT_MATRIXF4_EQ( (m1.transposition()), 1,1,1,1, 1,1,1,1, 1,1,1,1, 1,1,1,1);
    ASSERT_MATRIXF4_EQ( (m2.transposition()), 1,-2,-2,-42, 42,6,9,42, 5,-12,14.5,0, 0,0,0,1);
    ASSERT_MATRIXF4_EQ( (m3.transposition()), 1,-1,-22.5,0, 2,-2.5,8.5,0, 3,-3.2,32,0, 4,-4,-1.5,1);
}


// -----------------------------------------------------------------------------
// TESTS - perator overload
// -----------------------------------------------------------------------------
TEST_F(MatrixF4Test, multiply_by_matrix) {
    ASSERT_MATRIXF4_EQ((m1 * m1), 4,4,4,4, 4,4,4,4, 4,4,4,4, 4,4,4,4);
    ASSERT_MATRIXF4_EQ((m2 * m3),
            -153.5,     -60.5,  28.599991,  -171.5,
            262,        -121,   -409.2,     -14,
            -337.25,    96.75,  429.2,      -65.75,
            -84,        -189,   -260.4,     -335);
}

TEST_F(MatrixF4Test, multiply_by_vect4) {
    VectF4 v1(-2,-5,10,1.5);
    ASSERT_VECTF4_VALUES_EQ( (m1 * v1), 4.5, 4.5, 4.5, 4.5);
    ASSERT_VECTF4_VALUES_EQ( (m2 * v1), -162, -146, 104, -124.5);
    ASSERT_VECTF4_VALUES_EQ( (m3 * v1), 24, -23.5, 320.25, 1.5);
}

TEST_F(MatrixF4Test, multiply_by_scalar) {
    ASSERT_MATRIXF4_EQ( (m1 * 0.5), 0.5,0.5,0.5,0.5, 0.5,0.5,0.5,0.5, 0.5,0.5,0.5,0.5, 0.5,0.5,0.5,0.5);
    ASSERT_MATRIXF4_EQ( (m1 * 20), 20,20,20,20, 20,20,20,20, 20,20,20,20, 20,20,20,20);
    ASSERT_MATRIXF4_EQ( (m2 * 10), 10,420,50,0, -20,60,-120,0, -20,90,145,0, -420,420,0,10);
    ASSERT_MATRIXF4_EQ( (m3 * -4), -4,-8,-12,-16, 4,10,12.8,16, 90,-34,-128,6, 0,0,0,-4);
}

TEST_F(MatrixF4Test, equal_operator) {
    ASSERT_TRUE(m1 == m1);
    ASSERT_TRUE(m2 == m2);
    ASSERT_TRUE(m3 == m3);
}


} // End namespace



