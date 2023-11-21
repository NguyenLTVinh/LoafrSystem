#include "LoafrModel.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include "nlohmann/json.hpp"
#include <sstream>

LoafrModel::LoafrModel() {
  filter = std::make_unique<Filter>();
  search = std::make_unique<Search>();
  sort = std::make_unique<Sort>();
}

void LoafrModel::saveLogEntriesAsJson(
    const std::vector<std::string>& logEntries, const std::string& path,
    const std::string& baseFileName) {
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

    nlohmann::json jsonObj = {{"Timestamp", timestamp},
                              {"Component Name", componentName},
                              {"Event Type", eventType},
                              {"Data Field Name", dataFieldName},
                              {"Data Value", dataValue}};

    jsonArray.push_back(jsonObj);
  }

  std::string baseOutputFileName =
      baseFileName.substr(0, baseFileName.find_last_of('.')) + "-out";
  std::string outputFileName = baseOutputFileName + ".json";
  std::string outputPath =
      path.empty() ? outputFileName : path + "/" + outputFileName;
  int index = 1;
  while (std::filesystem::exists(outputPath)) {
    outputFileName =
        baseOutputFileName + "-" + std::to_string(index++) + ".json";
    outputPath = path.empty() ? outputFileName : path + "/" + outputFileName;
  }
  std::ofstream outFile(outputPath);
  if (outFile.is_open()) {
    outFile << jsonArray.dump(4);
    outFile.close();
  } else {
    std::cerr << "Unable to open file for writing: " << path << std::endl;
  }
}

void LoafrModel::SaveFilterLog(const NewDataEntry& newDataEntry,
                               const std::string& logItem,
                               const std::string& operation, const int val,
                               const std::string& path) {
  std::vector<std::string> matchedEntries;
  if (filter) {
    matchedEntries =
        filter->FilterLog(newDataEntry.getData(), logItem, operation, val);
  }
  saveLogEntriesAsJson(matchedEntries, path, newDataEntry.getFileName());
}

void LoafrModel::SaveSearchKeyword(const std::string& keyword,
                                   const NewDataEntry& newDataEntry,
                                   const std::string& path) {
  std::vector<std::string> matchedEntries;
  if (search) {
    matchedEntries = search->searchKeyword(keyword, newDataEntry.getData());
  }
  saveLogEntriesAsJson(matchedEntries, path, newDataEntry.getFileName());
}

void LoafrModel::sortFileByTimestamp(const std::string& sortType,
                                     const NewDataEntry& newDataEntry,
                                     const std::string& path) {
  std::vector<std::string> matchedEntries = newDataEntry.getData();
  if (sort) {
    matchedEntries = sort->sortFile(sortType, matchedEntries);
  }
  saveLogEntriesAsJson(matchedEntries, path, newDataEntry.getFileName());
}