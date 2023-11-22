#include <gtest/gtest.h>

#include <algorithm>
#include <nlohmann/json.hpp>

#include "../include/Sort.h"
#include "LoafrModel.h"

class SortTest : public ::testing::Test {
 protected:
  // Declare necessary variables
  Sort sorter; 
  std::vector<std::string> RandomlogEntries, ascendedlogEntries, descendedlogEntries, ascend, descend;

  void SetUp() override {
    // Populate the logEntries vector with test data
    RandomlogEntries = {
        "2023-11-14T08:35:00, patient simulator, glucose-monitor-report, "
        "sugar-level, 130",
        "2023-11-14T08:40:00, insulin pump, Start-Infusion, infusion-amount, 6",
        "2023-11-14T08:45:00, patient simulator, glucose-monitor-report, "
        "sugar-level, 178",
        "2023-11-14T08:50:00, insulin pump, Start-Infusion, infusion-amount, "
        "16",
        "2023-11-14T08:55:00, patient simulator, glucose-monitor-report, "
        "sugar-level, 173",
        "2023-11-14T09:00:00, patient simulator, glucose-monitor-report, "
        "sugar-level, 200",
        "2023-11-14T09:05:00, insulin pump, Start-Infusion, infusion-amount, "
        "18",
        "2023-11-14T09:10:00, patient simulator, glucose-monitor-report, "
        "sugar-level, 111",
        "2023-11-14T09:15:00, patient simulator, glucose-monitor-report, "
        "sugar-level, 125",
        "2023-11-14T08:30:00, patient simulator, glucose-monitor-report, "
        "sugar-level, 104"

    };

    ascendedlogEntries = {
        "2023-11-14T08:30:00, patient simulator, glucose-monitor-report, "
        "sugar-level, 104",
        "2023-11-14T08:35:00, patient simulator, glucose-monitor-report, "
        "sugar-level, 130",
        "2023-11-14T08:40:00, insulin pump, Start-Infusion, infusion-amount, 6",
        "2023-11-14T08:45:00, patient simulator, glucose-monitor-report, "
        "sugar-level, 178",
        "2023-11-14T08:50:00, insulin pump, Start-Infusion, infusion-amount, "
        "16",
        "2023-11-14T08:55:00, patient simulator, glucose-monitor-report, "
        "sugar-level, 173",
        "2023-11-14T09:00:00, patient simulator, glucose-monitor-report, "
        "sugar-level, 200",
        "2023-11-14T09:05:00, insulin pump, Start-Infusion, infusion-amount, "
        "18",
        "2023-11-14T09:10:00, patient simulator, glucose-monitor-report, "
        "sugar-level, 111",
        "2023-11-14T09:15:00, patient simulator, glucose-monitor-report, "
        "sugar-level, 125"

    };

    descendedlogEntries = {
      "2023-11-14T09:15:00, patient simulator, glucose-monitor-report, "
      "sugar-level, 125",
      "2023-11-14T09:10:00, patient simulator, glucose-monitor-report, "
      "sugar-level, 111",
      "2023-11-14T09:05:00, insulin pump, Start-Infusion, infusion-amount, 18",
      "2023-11-14T09:00:00, patient simulator, glucose-monitor-report, "
      "sugar-level, 200",
      "2023-11-14T08:55:00, patient simulator, glucose-monitor-report, "
      "sugar-level, 173",
      "2023-11-14T08:50:00, insulin pump, Start-Infusion, infusion-amount, 16",
      "2023-11-14T08:45:00, patient simulator, glucose-monitor-report, "
      "sugar-level, 178",
      "2023-11-14T08:40:00, insulin pump, Start-Infusion, infusion-amount, 6",
      "2023-11-14T08:35:00, patient simulator, glucose-monitor-report, "
      "sugar-level, 130",
      "2023-11-14T08:30:00, patient simulator, glucose-monitor-report, "
      "sugar-level, 104"

    };
  }
};

TEST_F(SortTest, AscendingSort) {
  ascend = sorter.sortFile("ascending", RandomlogEntries);

  EXPECT_EQ(ascend, ascendedlogEntries);
}

TEST_F(SortTest, DescendingSort) {
  descend = sorter.sortFile("descending", RandomlogEntries);

  EXPECT_EQ(descend, descendedlogEntries);
}

TEST_F(SortTest, EmptyLogEntries) {
  std::vector<std::string> emptyEntries;
  std::vector<std::string> result = sorter.sortFile("ascending", emptyEntries);

  EXPECT_TRUE(result.empty());
}

TEST_F(SortTest, InvalidSortType) {
  std::vector<std::string> logEntries = {"2023-01-01,Entry1"};

  testing::internal::CaptureStderr();
  std::vector<std::string> sortedEntries = sorter.sortFile("invalid", logEntries);
  std::string output = testing::internal::GetCapturedStderr();
  std::string expected_error = "Error: Invalid sort type";
  EXPECT_NE(output.find(expected_error), std::string::npos);
  ASSERT_EQ(sortedEntries, logEntries);
}
