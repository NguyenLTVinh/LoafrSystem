#include <gtest/gtest.h>
#include "filter.h"

class FilterTest : public ::testing::Test {
protected:  
  Filter filter;
  std::vector<std::string> logEntries;
  void SetUp() {


    logEntries = {
      "2023-11-14T08:30:00, patient simulator, glucose-monitor-report, sugar-level, 104",
      "2023-11-14T08:35:00, patient simulator, glucose-monitor-report, sugar-level, 130",
      "2023-11-14T08:40:00, insulin pump, Start-Infusion, infusion-amount, 6",
      "2023-11-14T08:45:00, patient simulator, glucose-monitor-report, sugar-level, 178",
      "2023-11-14T08:50:00, insulin pump, Start-Infusion, infusion-amount, 16"
    };
  }
  void TearDown() {}
};

// Demonstrate some basic assertions.
TEST_F(FilterTest, FilterLogLessThan) {
  std::vector<std::string> output = filter.FilterLog(logEntries, "sugar-level", "<", 170);
  EXPECT_EQ(output[0], logEntries[0]);
  EXPECT_EQ(output[1], logEntries[1]);
  EXPECT_EQ(output.size(), 2);
  
}
TEST_F(FilterTest, FilterLogGreaterThan){
  std::vector<std::string> output = filter.FilterLog(logEntries, "infusion-amount", ">", 3);
  EXPECT_EQ(output[0], logEntries[2]);
  EXPECT_EQ(output[1], logEntries[4]);
  EXPECT_EQ(output.size(), 2);
}
TEST_F(FilterTest, FilterLogEqual){
  std::vector<std::string> output = filter.FilterLog(logEntries, "infusion-amount", "=", 16);
  EXPECT_EQ(output[0], logEntries[4]);
  EXPECT_EQ(output.size(), 1);
}

TEST_F(FilterTest, NoMatched){
  std::vector<std::string> output = filter.FilterLog(logEntries, "sugar-level", ">", 600);
  EXPECT_EQ(output.size(), 0);
}
