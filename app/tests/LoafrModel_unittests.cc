#include <gtest/gtest.h>
#include "LoafrModel.h"
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>

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
    std::string baseFileName = "testLog.json";
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
    std::string baseFileName = "testLog.json";
    model.saveLogEntriesAsJson(logEntries, path, baseFileName);
    std::string expectedFileName = path + "/testLog-out.json";
    ASSERT_TRUE(std::filesystem::exists(expectedFileName));
}

TEST_F(LoafrModelTest, VerifyOutputFileContent) {
    std::vector<std::string> logEntries = {
        "2023-01-01,Component1,Event1,Field1,Value1",
        "2023-01-02,Component2,Event2,Field2,Value2"
    };
    std::string path = "/tmp";
    std::string baseFileName = "testLog.json";
    model.saveLogEntriesAsJson(logEntries, path, baseFileName);
    std::string expectedFileName = path + "/testLog-out.json";
    std::ifstream inFile(expectedFileName);
    ASSERT_TRUE(inFile.is_open());
    std::stringstream buffer;
    buffer << inFile.rdbuf();
    std::string fileContent = buffer.str();
    nlohmann::json parsedJson = nlohmann::json::parse(fileContent);
    nlohmann::json expectedJson = {
        {
            {"Timestamp", "2023-01-01"},
            {"Component Name", "Component1"},
            {"Event Type", "Event1"},
            {"Data Field Name", "Field1"},
            {"Data Value", "Value1"}
        },
        {
            {"Timestamp", "2023-01-02"},
            {"Component Name", "Component2"},
            {"Event Type", "Event2"},
            {"Data Field Name", "Field2"},
            {"Data Value", "Value2"}
        }
    };
    ASSERT_EQ(parsedJson, expectedJson);
}
