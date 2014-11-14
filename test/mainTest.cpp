#include "gtest/gtest.h"

class TestClassName : public ::testing::Test {
  protected:
    virtual void SetUp() {}
    virtual void TearDown() {}
};

TEST_F(TestClassName, TestInstanceName) {
  EXPECT_TRUE(1);
}
