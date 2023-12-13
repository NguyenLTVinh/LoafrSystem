#include <gtest/gtest.h>

#include "filter.h"

class FilterTest : public ::testing::Test {
 protected:
  Filter filter;
  std::vector<std::string> logEntries;
  std::vector<std::string> advancedLogEntries;
  void SetUp() {
    logEntries = {
        "2023-11-14T08:30:00, patient simulator, glucose-monitor-report, "
        "sugar-level, 104",
        "2023-11-14T08:35:00, patient simulator, glucose-monitor-report, "
        "sugar-level, 130",
        "2023-11-14T08:40:00, insulin pump, Start-Infusion, infusion-amount, 6",
        "2023-11-14T08:45:00, patient simulator, glucose-monitor-report, "
        "sugar-level, 178",
        "2023-11-14T08:50:00, insulin pump, Start-Infusion, infusion-amount, "
        "16"};

    advancedLogEntries = {
        "2023-11-14T08:50:00, insulin pump, Start-Infusion, infusion-amount, "
        "-1, 17",
        "2023-11-14T08:55:00, insulin pump, Start-Infusion, infusion-amount, "
        "-1, 7",
        "2023-11-14T09:00:00, insulin pump, Start-Infusion, infusion-amount, "
        "-1, 6",
        "2023-11-14T08:30:00, patient simulator, glucose-monitor-report, "
        "infusion-amount, -1, 17",
        "2023-11-14T08:35:00, patient simulator, glucose-monitor-report, "
        "infusion-amount, 0, 130"
        // Add more log entries as needed
    };
  };

  void TearDown() {}
};

// Demonstrate some basic assertions.
TEST_F(FilterTest, FilterLogLessThan) {
  std::vector<std::string> output =
      filter.FilterLog(logEntries, "sugar-level", "<", 170);
  EXPECT_EQ(output[0], logEntries[0]);
  EXPECT_EQ(output[1], logEntries[1]);
  EXPECT_EQ(output.size(), 2);
}
TEST_F(FilterTest, FilterLogGreaterThan) {
  std::vector<std::string> output =
      filter.FilterLog(logEntries, "infusion-amount", ">", 3);
  EXPECT_EQ(output[0], logEntries[2]);
  EXPECT_EQ(output[1], logEntries[4]);
  EXPECT_EQ(output.size(), 2);
}
TEST_F(FilterTest, FilterLogEqual) {
  std::vector<std::string> output =
      filter.FilterLog(logEntries, "infusion-amount", "=", 16);
  EXPECT_EQ(output[0], logEntries[4]);
  EXPECT_EQ(output.size(), 1);
}

TEST_F(FilterTest, NoMatched) {
  std::vector<std::string> output =
      filter.FilterLog(logEntries, "sugar-level", ">", 600);
  EXPECT_EQ(output.size(), 0);
}

TEST_F(FilterTest, NoStartEvent) {
  std::vector<std::vector<std::string>> output = filter.FilterByStartEndEvents(
      advancedLogEntries, "NonexistentStartEvent", "glucose-monitor-report");
  EXPECT_TRUE(output.empty());
}

TEST_F(FilterTest, NoMatchingEvents) {
  std::vector<std::vector<std::string>> output = filter.FilterByStartEndEvents(
      advancedLogEntries, "NonexistentStartEvent", "NonexistentEndEvent");

  EXPECT_TRUE(output.empty());
}

TEST_F(FilterTest, NoEndEvent) {
  std::vector<std::vector<std::string>> output = filter.FilterByStartEndEvents(
      advancedLogEntries, "Start-Infusion", "NonexistentEndEvent");
  std::vector<std::vector<std::string>> expected;

  expected.push_back(
      {"2023-11-14T08:50:00, insulin pump, Start-Infusion, infusion-amount, "
       "-1, 17",
       "2023-11-14T08:55:00, insulin pump, Start-Infusion, infusion-amount, "
       "-1, 7",
       "2023-11-14T09:00:00, insulin pump, Start-Infusion, infusion-amount, "
       "-1, 6",
       "2023-11-14T08:30:00, patient simulator, glucose-monitor-report, "
       "infusion-amount, -1, 17",
       "2023-11-14T08:35:00, patient simulator, glucose-monitor-report, "
       "infusion-amount, 0, 130"});

  EXPECT_EQ(output, expected);
}

TEST_F(FilterTest, StartAndEnd) {
  std::vector<std::vector<std::string>> output = filter.FilterByStartEndEvents(
      advancedLogEntries, "Start-Infusion", "glucose-monitor-report");

  std::vector<std::vector<std::string>> expected;

  expected.push_back(
      {{"2023-11-14T08:50:00, insulin pump, Start-Infusion, infusion-amount, "
        "-1, 17",
        "2023-11-14T08:55:00, insulin pump, Start-Infusion, infusion-amount, "
        "-1, 7",
        "2023-11-14T09:00:00, insulin pump, Start-Infusion, infusion-amount, "
        "-1, 6",
        "2023-11-14T08:30:00, patient simulator, glucose-monitor-report, "
        "infusion-amount, -1, 17"}});

  EXPECT_EQ(output, expected);
}
