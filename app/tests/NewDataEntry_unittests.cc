#include <filesystem>
#include <gtest/gtest.h>

#include "NewDataEntry.h"

class NewDataEntryTest : public ::testing::Test {
public:
  void SetUp() {
    // code here will execute just before the test ensues
    std::string directory(std::filesystem::current_path());
    directory.append("/tests");
    test1 = new NewDataEntry("test1.txt", directory);
    test1->loadData();
    test2 = new NewDataEntry("example1.txt", "");
  }
  void TearDown() {}

protected:
  NewDataEntry *test1;
  NewDataEntry *test2;
};

TEST_F(NewDataEntryTest, GetFileNameTest) {
  EXPECT_EQ(test1->getFileName(), "test1.txt");
  EXPECT_EQ(test2->getFileName(), "example1.txt");
}

TEST_F(NewDataEntryTest, GetPathTest) {
  std::string path(std::filesystem::current_path());
  path.append("/tests");
  EXPECT_EQ(test1->getPath(), path);
  EXPECT_EQ(test2->getPath(), "");
}

TEST_F(NewDataEntryTest, GetDataTest) {
  EXPECT_GT(test1->getData().size(), 0);
  EXPECT_EQ(test2->getData().size(), 0);
}
