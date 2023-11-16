#include "LoafrModel.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <nlohmann/json.hpp>

LoafrModel::LoafrModel() {
    filter = new Filter();
    search = new Search();
}

LoafrModel::~LoafrModel() {
    delete filter;
    delete search;
}

void LoafrModel::loadLogFile(const std::string& filePath, const std::string& fileName) {
    //std::string fullPath = filePath + "/" + fileName;
    std::string fullPath = fileName;
    std::ifstream file(fullPath);
    std::string line;

    if (file.is_open()) {
        std::cout << "Loaded " << fullPath << std::endl;
        while (getline(file, line)) {
            logEntries.push_back(line);
        }
        file.close();
    } else {
        std::cerr << "Unable to open file: " << fullPath << std::endl;
    }
}

const std::vector<std::string>& LoafrModel::getLogEntries() const {
    return logEntries;
}

void LoafrModel::saveLogEntriesAsJson(const std::vector<std::string>& logEntries, const std::string& path) {
    nlohmann::json jsonArray;

    for (const auto& entry : logEntries) {
        std::istringstream iss(entry);
        std::string timestamp, componentName, eventType, dataFieldName, dataValue;

        getline(iss, timestamp, ',');
        getline(iss, componentName, ',');
        getline(iss, eventType, ',');
        getline(iss, dataFieldName, ',');
        getline(iss, dataValue, ',');

        auto trim = [](std::string& s) { s.erase(0, s.find_first_not_of(" ")); };
        trim(componentName);
        trim(eventType);
        trim(dataFieldName);
        trim(dataValue);

        nlohmann::json jsonObj = {
            {"Timestamp", timestamp},
            {"Component Name", componentName},
            {"Event Type", eventType},
            {"Data Field Name", dataFieldName},
            {"Data Value", dataValue}
        };

        jsonArray.push_back(jsonObj);
    }
    // TODO: come up with naming convention for this.
    std::string outputPath = path;
    outputPath += "/filtered_output.json";
    std::ofstream outFile(outputPath);
    if (outFile.is_open()) {
        outFile << jsonArray.dump(4);
        outFile.close();
    } else {
        std::cerr << "Unable to open file for writing: " << path << std::endl;
    }
}

void LoafrModel::SaveFilterLog(const std::vector<std::string>& logEntries, 
                                       const std::string& logItem, 
                                       const std::string& operation, 
                                       const int val, const std::string& path) {
    std::vector<std::string> matchedEntries;
    if (filter) {
        matchedEntries =  filter->FilterLog(logEntries, logItem, operation, val);
    }
    saveLogEntriesAsJson(matchedEntries, path);
}

void LoafrModel::SaveSearchKeyword(const std::string& keyword, const std::vector<std::string>& logEntries, const std::string& path) {
    std::vector<std::string> matchedEntries;
    if (search) {
        matchedEntries =  search->searchKeyword(keyword, logEntries);
    }
    saveLogEntriesAsJson(matchedEntries, path);
}