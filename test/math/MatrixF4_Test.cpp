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
#define ASSERT_MATRIXF4_EQ(Matrix, m11,m12,m13,m14, m21,m22,m23,m24, m31,m32,m33,m34, m41,m42,m43,m44) \
    ASSERT_FLOAT_EQ(Matrix.m[0][0],m11); \
    ASSERT_FLOAT_EQ(Matrix.m[0][1], m12); \
    ASSERT_FLOAT_EQ(Matrix.m[0][2], m13); \
    ASSERT_FLOAT_EQ(Matrix.m[0][3], m14); \
    \
    ASSERT_FLOAT_EQ(Matrix.m[1][0], m11); \
    ASSERT_FLOAT_EQ(Matrix.m[1][1], m12); \
    ASSERT_FLOAT_EQ(Matrix.m[1][2], m13); \
    ASSERT_FLOAT_EQ(Matrix.m[1][3], m14); \
    \
    ASSERT_FLOAT_EQ(Matrix.m[2][0], m11); \
    ASSERT_FLOAT_EQ(Matrix.m[2][1], m12); \
    ASSERT_FLOAT_EQ(Matrix.m[2][2], m13); \
    ASSERT_FLOAT_EQ(Matrix.m[2][3], m14); \
    \
    ASSERT_FLOAT_EQ(Matrix.m[3][0], m11); \
    ASSERT_FLOAT_EQ(Matrix.m[3][1], m12); \
    ASSERT_FLOAT_EQ(Matrix.m[3][2], m13); \
    ASSERT_FLOAT_EQ(Matrix.m[3][3], m14)


namespace {

// ----------------------------------------------------------------------------
// Fixture object to test Matrix
// ----------------------------------------------------------------------------
class MatrixF4Test : public ::testing::Test {
    protected:
        virtual void SetUp() {
        }
        virtual void TearDown() {
        }
};


// -----------------------------------------------------------------------------
// TESTS - MatrixF4 functions
// -----------------------------------------------------------------------------
TEST_F(MatrixF4Test, multiply) {
    MatrixF4 m1(
            VectF4(1,1,1,1),
            VectF4(1,1,1,1),
            VectF4(1,1,1,1),
            VectF4(1,1,1,1)
        );
    MatrixF4 m2 = m1 * m1;
    ASSERT_MATRIXF4_EQ(m2, 4,4,4,4, 4,4,4,4, 4,4,4,4, 4,4,4,4);
}


} // End namespace


