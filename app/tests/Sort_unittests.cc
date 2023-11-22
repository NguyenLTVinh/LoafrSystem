#include <gtest/gtest.h>
#include "Sort.h"

class SortTest : public ::testing::Test {
protected:
    Sort sortInstance;
};

TEST_F(SortTest, SortAscending) {
    std::vector<std::string> logEntries = {
        "2023-01-03,Entry3",
        "2023-01-01,Entry1",
        "2023-01-02,Entry2"
    };
    auto sortedEntries = sortInstance.sortFile("ascending", logEntries);

    std::vector<std::string> expected = {
        "2023-01-01,Entry1",
        "2023-01-02,Entry2",
        "2023-01-03,Entry3"
    };

    ASSERT_EQ(sortedEntries, expected);
}

TEST_F(SortTest, SortDescending) {
    std::vector<std::string> logEntries = {
        "2023-01-01,Entry1",
        "2023-01-03,Entry3",
        "2023-01-02,Entry2"
    };
    auto sortedEntries = sortInstance.sortFile("descending", logEntries);

    std::vector<std::string> expected = {
        "2023-01-03,Entry3",
        "2023-01-02,Entry2",
        "2023-01-01,Entry1"
    };

    ASSERT_EQ(sortedEntries, expected);
}

TEST_F(SortTest, HandleEmptyLogEntries) {
    std::vector<std::string> logEntries;
    auto sortedEntries = sortInstance.sortFile("ascending", logEntries);

    ASSERT_TRUE(sortedEntries.empty());
}

TEST_F(SortTest, InvalidSortType) {
    std::vector<std::string> logEntries = {"2023-01-01,Entry1"};
    
    testing::internal::CaptureStderr();
    auto sortedEntries = sortInstance.sortFile("invalid", logEntries);
    std::string output = testing::internal::GetCapturedStderr();
    std::string expected_error = "Error: Invalid sort type";
    EXPECT_NE(output.find(expected_error), std::string::npos);
    ASSERT_EQ(sortedEntries, logEntries);
}
