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

#define ASSERT_VECTF3_VALUES_EQ(vect, X, Y, Z) \
    ASSERT_FLOAT_EQ(vect.x, X); \
    ASSERT_FLOAT_EQ(vect.y, Y); \
    ASSERT_FLOAT_EQ(vect.z, Z)


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

TEST_F(MatrixTransformTest, creaTranslate) {
    MatrixF4 mm1 = MatrixTransform::creaTranslate(32, -2, 7.9);
    MatrixF4 mm2 = MatrixTransform::creaTranslate(VectF3(32, -2, 7.9));
    ASSERT_MATRIXF4_EQ(mm1, 1,0,0,32, 0,1,0,-2, 0,0,1,7.9, 0,0,0,1);
    ASSERT_MATRIXF4_EQ(mm2, 1,0,0,32, 0,1,0,-2, 0,0,1,7.9, 0,0,0,1);
}

TEST_F(MatrixTransformTest, creaScale) {
    MatrixF4 mm1 = MatrixTransform::creaScale(VectF3(8.9, -0.2, 9.2));
    MatrixF4 mm2 = MatrixTransform::creaScale(8.9, -0.2, 9.2);
    ASSERT_MATRIXF4_EQ(mm1, 8.9,0,0,0, 0,-0.2,0,0, 0,0,9.2,0, 0,0,0,1);
    ASSERT_MATRIXF4_EQ(mm2, 8.9,0,0,0, 0,-0.2,0,0, 0,0,9.2,0, 0,0,0,1);
}

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

TEST_F(MatrixTransformTest, creaRotateZYX_floats) {
    MatrixF4 mm1 = MatrixTransform::creaRotateZYX(0,0,0);
    ASSERT_MATRIXF4_EQ(mm1, 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);
    // TODO Add more tests
}

TEST_F(MatrixTransformTest, creaRotateZYX_VectF3) {
    VectF3 v1(0.0f, 0.0f, 0.0f);
    MatrixF4 mm1 = MatrixTransform::creaRotateZYX(v1);
    ASSERT_MATRIXF4_EQ(mm1, 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);
    // TODO Add more tests
}

TEST_F(MatrixTransformTest, creaLookAtLH) {
    // Test 1
    VectF3 cPos(4.0f), cTarget(150.0f), cUp(0,1,0);
    MatrixF4 mm1 = MatrixTransform::creaLookAtLH(cPos, cTarget, cUp);
    ASSERT_MATRIXF4_EQ(mm1,
        0.707107, 0.000000, -0.707107, -0.000000,
        -0.40824828, 0.81649655, -0.40824828, -0.000000,
        0.577350, 0.577350, 0.577350, -6.928203,
        0.000000, 0.000000, 0.000000, 1.000000);
    // Test 2
    VectF3 cPos2(0.0f), cTarget2(10.0f), cUp2(0,1,0);
    MatrixF4 mm2 = MatrixTransform::creaLookAtLH(cPos2, cTarget2, cUp2);
    ASSERT_MATRIXF4_EQ(mm2,
        0.707107, 0.000000, -0.707107, -0.000000,
        -0.40824828, 0.81649655, -0.40824828, -0.000000,
        0.577350, 0.577350, 0.577350, -0.000000,
        0.000000, 0.000000, 0.000000, 1.000000);
}

TEST_F(MatrixTransformTest, creaPerspectiveFovLH) {
    MatrixF4 mm1 = MatrixTransform::creaPerspectiveFovLH(1.57f, 960, 540, 1.0f, 45.0f);
    ASSERT_MATRIXF4_EQ(mm1,
        0.562948048, 0, 0, 0,
        0, 1.00079656, 0, 0,
        0, 0, 1.02272725, -1.02272725,
        0, 0, 1, 0);
    // TODO Add more tests
}

TEST_F(MatrixTransformTest, projectOnScreen) {
    // Test1
    MatrixF4 mTransform(
        -0.216998681, 0, 0.519443989, 0,
        0, 1.00079656, 0, 0,
        -0.943691969, 0, -0.394229025, 3.06818175,
        -0.922721028, 0, -0.385468394, 4);
    VectF3 point(-0.718800008, 0.0390999988, 0.1875);
    VectF3 project = MatrixTransform::projectOnScreen(point, mTransform, 960, 540);
    ASSERT_VECTF3_VALUES_EQ(project, 532.982056, 265.39731, 0.799958229);
    // TODO Add more tests
}



} // End namespace



