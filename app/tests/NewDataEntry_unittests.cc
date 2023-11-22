#include "NewDataEntry.h"
#include <gtest/gtest.h>

class NewDataEntryTest : public ::testing::Test {
public:
  void SetUp() {
    // code here will execute just before the test ensues
    test1 = new NewDataEntry("temp1.txt", "../tests");
    test2 = new NewDataEntry("example1.txt", "");
  }
  void TearDown() {}

protected:
  NewDataEntry *test1;
  NewDataEntry *test2;
};

TEST_F(NewDataEntryTest, GetFileNameTest) {
  EXPECT_EQ(test1->getFileName(), "temp1.txt");
  EXPECT_EQ(test2->getFileName(), "example1.txt");
}

TEST_F(NewDataEntryTest, GetPathTest) {
  EXPECT_EQ(test1->getPath(), "../tests");
  EXPECT_EQ(test2->getPath(), "");
}
