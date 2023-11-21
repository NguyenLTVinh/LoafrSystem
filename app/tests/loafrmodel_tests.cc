#include <gtest/gtest.h>

class LoafrModelTest : public ::testing::Test {
public:
  void SetUp() {
    // code here will execute just before the test ensues
  }
  void TearDown() {}

protected:
};

// Demonstrate some basic assertions.
TEST(LoafrModelTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}
