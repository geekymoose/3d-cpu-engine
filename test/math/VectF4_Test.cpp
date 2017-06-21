#include <iostream>

#include "gtest/gtest.h"
#include "math/VectF4.h"


namespace {


// ----------------------------------------------------------------------------
// Fixture object to test VectF4
// ----------------------------------------------------------------------------
class VectF4Test : public ::testing::Test {
    // Attributes
    protected:
        VectF4 v0;
        VectF4 v1;
        VectF4 v2;
        VectF4 v3;
        VectF4 v4;

    // Init
    protected:
        VectF4Test()
            : v1(1.0f, 2.0f, 3.0f, 4.0f),
              v2(5.5f, 3.5f, -1.0f, 10.0f),
              v3(-10.0f, 2.1f, -2.1f, -2.8f),
              v4(42.0f, 42.0f, 42.0f, 42.0f) {
        }

        virtual ~VectF4Test() {
        }

        virtual void SetUp() {
        }

        virtual void TearDown() {
        }
};


// ----------------------------------------------------------------------------
// VectF4 tests
// ----------------------------------------------------------------------------
TEST_F(VectF4Test, constructors) {
    //TODO
    ASSERT_EQ(0,1) << "TODO";
}

TEST_F(VectF4Test, setters) {
    //TODO
    ASSERT_EQ(0,1) << "TODO";
}


// -----------------------------------------------------------------------------
// VectF4 functions TESTS
// -----------------------------------------------------------------------------
TEST_F(VectF4Test, length) {
    ASSERT_EQ(v0.length(), 0);
    ASSERT_FLOAT_EQ(v1.length(), 5.4772255);
    ASSERT_FLOAT_EQ(v2.length(), 11.979148);
    ASSERT_FLOAT_EQ(v3.length(), 10.800925);
    ASSERT_EQ(v4.length(), 84.0);
}

TEST_F(VectF4Test, squareLength) {
    ASSERT_EQ(v0.squareLength(), 0);
    ASSERT_FLOAT_EQ(v1.squareLength(), 30);
}

TEST_F(VectF4Test, length3) {
    ASSERT_EQ(v0.length3(), 0);
    ASSERT_FLOAT_EQ(v1.length3(), 3.7416573);
}

TEST_F(VectF4Test, squareLength3) {
    ASSERT_EQ(v0.squareLength3(), 0);
    ASSERT_FLOAT_EQ(v1.squareLength3(), 14);
    ASSERT_FLOAT_EQ(v2.squareLength3(), 143.5);
}

TEST_F(VectF4Test, normalize) {
    //TODO
    ASSERT_EQ(0,1) << "TODO";
}

TEST_F(VectF4Test, normalize3) {
    //TODO
    ASSERT_EQ(0,1) << "TODO";
}

TEST_F(VectF4Test, crossProduct3) {
    //TODO
    ASSERT_EQ(0,1) << "TODO";
}

TEST_F(VectF4Test, dotProduct) {
    //TODO
    ASSERT_EQ(0,1) << "TODO";
}

TEST_F(VectF4Test, dotProduct3) {
    //TODO
    ASSERT_EQ(0,1) << "TODO";
}


// -----------------------------------------------------------------------------
// Operators overload TESTS
// -----------------------------------------------------------------------------
TEST_F(VectF4Test, equal) {
    //TODO
    ASSERT_EQ(0,1) << "TODO";
}

TEST_F(VectF4Test, notequal) {
    //TODO
    ASSERT_EQ(0,1) << "TODO";
}

TEST_F(VectF4Test, multiply) {
    //TODO
    ASSERT_EQ(0,1) << "TODO";
}

TEST_F(VectF4Test, divide) {
    //TODO
    ASSERT_EQ(0,1) << "TODO";
}

TEST_F(VectF4Test, add) {
    //TODO
    ASSERT_EQ(0,1) << "TODO";
}

TEST_F(VectF4Test, substract) {
    //TODO
    ASSERT_EQ(0,1) << "TODO";
}

// *= /= += -=
TEST_F(VectF4Test, multiplyinplace) {
    //TODO
    ASSERT_EQ(0,1) << "TODO";
}

TEST_F(VectF4Test, divideinplace) {
    //TODO
    ASSERT_EQ(0,1) << "TODO";
}

TEST_F(VectF4Test, addinplace) {
    //TODO
    ASSERT_EQ(0,1) << "TODO";
}

TEST_F(VectF4Test, substractinplace) {
    //TODO
    ASSERT_EQ(0,1) << "TODO";
}

} // End namespace


