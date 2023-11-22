#include <gtest/gtest.h>

#include "Search.h"

class SearchTest : public ::testing::Test {
 protected:
  Search search;
  std::vector<std::string> logEntries;

  void SetUp() override {
    logEntries = {
        "2023-11-14T09:10:00, insulin pump, Start-Infusion, infusion-amount, "
        "10",
        "2023-11-14T09:15:00, patient simulator, glucose-monitor-report, "
        "sugar-level, 125",
        "2023-11-14T09:20:00, insulin pump, Stop-Infusion, infusion-amount, 0",
        "2023-11-14T09:25:00, patient monitor, heart-rate, bpm, 80",
        "2023-11-14T09:30:00, patient simulator, insulin-level, level, 5"};
  }

  void TearDown() override {}
};

TEST_F(SearchTest, KeywordPresentMultipleTimes) {
  std::vector<std::string> result =
      search.searchKeyword("insulin pump", logEntries);
  ASSERT_EQ(result.size(), 2u);
  EXPECT_EQ(result[0], logEntries[0]);
  EXPECT_EQ(result[1], logEntries[2]);
}

TEST_F(SearchTest, KeywordPresentOneTime) {
  std::vector<std::string> result =
      search.searchKeyword("heart-rate", logEntries);
  ASSERT_EQ(result.size(), 1u);
  EXPECT_EQ(result[0], logEntries[3]);
}

TEST_F(SearchTest, CaseSensitivity) {
  std::vector<std::string> result =
      search.searchKeyword("Insulin Pump", logEntries);
  EXPECT_TRUE(result.empty());
}

TEST_F(SearchTest, PartialKeyword) {
  std::vector<std::string> result = search.searchKeyword("insulin", logEntries);
  ASSERT_EQ(result.size(), 3u);
}

TEST_F(SearchTest, NumberValue) {
  std::vector<std::string> result = search.searchKeyword("80", logEntries);
  ASSERT_EQ(result.size(), 1u);
  EXPECT_EQ(result[0], logEntries[3]);
}

TEST_F(SearchTest, NonExistingKeyword) {
  std::vector<std::string> result = search.searchKeyword("bruh", logEntries);
  EXPECT_TRUE(result.empty());
}

TEST_F(SearchTest, KeywordMatchingFieldName) {
  std::vector<std::string> result =
      search.searchKeyword("infusion-amount", logEntries);
  ASSERT_EQ(result.size(), 2u);
}
