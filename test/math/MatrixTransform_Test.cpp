// -----------------------------------------------------------------------------
// Unit Tests for MatrixTransform class
// GoogleTest Framework
//
// Author: Constantin Masson
// -----------------------------------------------------------------------------
#include <iostream>

#include "gtest/gtest.h"
#include "math/MatrixTransform.h"


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
class MatrixTransformTest : public ::testing::Test {
    protected:
        MatrixTransformTest() {}
        virtual void SetUp() {}
        virtual void TearDown() {}
};

TEST_F(MatrixTransformTest, creaRotateX) {
    MatrixF4 mm1 = MatrixTransform::creaRotateX(0);
    ASSERT_MATRIXF4_EQ(mm1, 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);
    // TODO Some more
}

TEST_F(MatrixTransformTest, creaRotateY) {
    MatrixF4 mm1 = MatrixTransform::creaRotateY(0);
    ASSERT_MATRIXF4_EQ(mm1, 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);
    // TODO Some more
}

TEST_F(MatrixTransformTest, creaRotateZ) {
    MatrixF4 mm1 = MatrixTransform::creaRotateZ(0);
    ASSERT_MATRIXF4_EQ(mm1, 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);
    // TODO Some more
}


} // End namespace



