#include <gtest/gtest.h>
#include "LoafrModel.h"
#include <filesystem>
#include <fstream>

class LoafrModelTest : public ::testing::Test {
protected:
    LoafrModel model;
    void SetUp() override {
    }
    void TearDown() override {
    }
};

TEST_F(LoafrModelTest, SaveEmptyLogEntries) {
    std::vector<std::string> logEntries;
    std::string path = "/tmp";
    std::string baseFileName = "testLog.txt";
    model.saveLogEntriesAsJson(logEntries, path, baseFileName);
    std::string expectedFileName = path + "/testLog-out.json";
    ASSERT_TRUE(std::filesystem::exists(expectedFileName));
}

TEST_F(LoafrModelTest, SaveNonEmptyLogEntries) {
    std::vector<std::string> logEntries = {
        "2023-01-01, Component1, Event1, Field1, Value1",
        "2023-01-02, Component2, Event2, Field2, Value2"
    };
    std::string path = "/tmp";
    std::string baseFileName = "testLog.txt";
    model.saveLogEntriesAsJson(logEntries, path, baseFileName);
    std::string expectedFileName = path + "/testLog-out.json";
    ASSERT_TRUE(std::filesystem::exists(expectedFileName));
}

TEST_F(LoafrModelTest, VerifyOutputFileContent) {
    std::vector<std::string> logEntries = {
        "2023-01-01, Component1, Event1, Field1, Value1",
        "2023-01-02, Component2, Event2, Field2, Value2"
    };
    std::string path = "/tmp";
    std::string baseFileName = "testLogVerify.txt";
    model.saveLogEntriesAsJson(logEntries, path, baseFileName);
    std::string expectedFileName = path + "/testLogVerify-out.json";
    std::ifstream outFile(expectedFileName);
    ASSERT_TRUE(outFile.is_open());
    std::string fileContentStr((std::istreambuf_iterator<char>(outFile)), std::istreambuf_iterator<char>());

    // Function to replace newlines and tabs with spaces and remove extra spaces
    auto formatJsonString = [](std::string& str) {
        std::replace(str.begin(), str.end(), '\n', ' ');
        std::replace(str.begin(), str.end(), '\t', ' ');
        str.erase(std::unique(str.begin(), str.end(), [](char a, char b) { return a == ' ' && b == ' '; }), str.end());
    };
    formatJsonString(fileContentStr);
    std::string jsonStr = R"([ { "Component Name": "Component1", "Data Field Name": "Field1", "Data Value": "Value1", "Event Type": "Event1", "Timestamp": "2023-01-01" }, { "Component Name": "Component2", "Data Field Name": "Field2", "Data Value": "Value2", "Event Type": "Event2", "Timestamp": "2023-01-02" } ])";
    ASSERT_EQ(jsonStr, fileContentStr);

}
