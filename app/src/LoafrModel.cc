#include "LoafrModel.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

/**
 * @brief Constructs a new LoafrModel object.
 *
 * The constructor initializes unique pointers to Filter, Search, and Sort
 * objects, which are used for filtering, searching, and sorting the log
 * entries.
 */
LoafrModel::LoafrModel() {
  filter = std::make_unique<Filter>();
  search = std::make_unique<Search>();
  sort = std::make_unique<Sort>();
}

/**
 * @brief Saves log entries as a JSON file.
 *
 * @param logEntries A vector of strings containing log entries to be saved.
 * @param path The directory path where the JSON file will be saved.
 * @param baseFileName The base name of the file used to create the output file
 * name.
 */
void LoafrModel::saveLogEntriesAsJson(
    const std::vector<std::string> &logEntries, const std::string &path,
    const std::string &baseFileName) {
  nlohmann::json jsonArray;

  for (const auto &entry : logEntries) {
    std::istringstream iss(entry);
    std::string timestamp, componentName, eventType, dataFieldName, dataValue;

    getline(iss, timestamp, ',');
    getline(iss, componentName, ',');
    getline(iss, eventType, ',');
    getline(iss, dataFieldName, ',');
    getline(iss, dataValue, ',');

    auto trim = [](std::string &s) { s.erase(0, s.find_first_not_of(" ")); };
    trim(componentName);
    trim(eventType);
    trim(dataFieldName);
    trim(dataValue);
    if (!dataValue.empty() && dataValue[dataValue.size() - 1] == '\r') {
      dataValue.erase(dataValue.size() - 1);
    }

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

/**
 * @brief Filters log entries based on specified criteria and saves the
 * results as JSON.
 *
 * @param newDataEntry The NewDataEntry object containing log entries.
 * @param logItem The field name to filter on.
 * @param operation The comparison operation ("<", "=", ">").
 * @param val The value to compare against.
 * @param path The directory path where the filtered JSON file will be saved.
 */
void LoafrModel::SaveFilterLog(const NewDataEntry &newDataEntry,
                               const std::string &logItem,
                               const std::string &operation, const int val,
                               const std::string &path) {
  std::vector<std::string> matchedEntries;
  if (filter) {
    matchedEntries =
        filter->FilterLog(newDataEntry.getData(), logItem, operation, val);
  }
  saveLogEntriesAsJson(matchedEntries, path, newDataEntry.getFileName());
}

/**
 * @brief Filters log entries bases on start and end event times and
 * saves the results as JSON
 *
 * @param newDataEntry The NewDataEntry object containing log entries.
 * @param StartEventName the name of the starting event
 * @param EndEventName the name of the ending event
 *
 */
void LoafrModel::saveFilterByStartEndEventsToLog(
    const NewDataEntry &newDataEntry, const std::string &StartEventName,
    const std::string &EndEventName, const std::string &path) {

  std::vector<std::vector<std::string>> matchedEntries;
  if (filter) {
    matchedEntries = filter->FilterByStartEndEvents(
        newDataEntry.getData(), StartEventName, EndEventName);
  }
  for (std::vector<std::string> &line : matchedEntries) {
    saveLogEntriesAsJson(line, path, newDataEntry.getFileName());
  }
}

void LoafrModel::saveAdvancedFilter(const NewDataEntry &newDataEntry,
                                   const std::string &StartEventName,
                                   const std::string &EndEventName,
                                   const std::string &logItem,
                                   const std::string &operation, 
                                   const int val,
                                   const std::string &path) {
    // Step 1: Call FilterByStartEndEvents
    auto groupedEntries = filter->FilterByStartEndEvents(newDataEntry.getData(), StartEventName, EndEventName);

    // Step 2: For each group, call FilterLog and store the results
    std::vector<std::vector<std::string>> filteredGroups;
    for (auto &group : groupedEntries) {
        auto filteredGroup = filter->FilterLog(group, logItem, operation, val);
        if (!filteredGroup.empty()) {
            filteredGroups.push_back(filteredGroup);
        }
    }

    // Step 3: Save each filtered group to JSON
    for (const auto &group : filteredGroups) {
        saveLogEntriesAsJson(group, path, newDataEntry.getFileName());
    }
}

/**
 * @brief Searches for a keyword in log entries and saves the results as JSON.
 *
 * @param keyword The keyword to search for.
 * @param newDataEntry The NewDataEntry object containing log entries.
 * @param path The directory path where the search results JSON file will be
 * saved.
 */
void LoafrModel::SaveSearchKeyword(const std::string &keyword,
                                   const NewDataEntry &newDataEntry,
                                   const std::string &path) {
  std::vector<std::string> matchedEntries;
  if (search) {
    matchedEntries = search->searchKeyword(keyword, newDataEntry.getData());
  }
  saveLogEntriesAsJson(matchedEntries, path, newDataEntry.getFileName());
}

/**
 * @brief Sorts log entries by timestamp and saves them as JSON.
 *
 * @param sortType The type of sorting ("ascending" or "descending").
 * @param newDataEntry The NewDataEntry object containing log entries.
 * @param path The directory path where the sorted JSON file will be saved.
 */
void LoafrModel::sortFileByTimestamp(const std::string &sortType,
                                     const NewDataEntry &newDataEntry,
                                     const std::string &path) {
  std::vector<std::string> matchedEntries = newDataEntry.getData();
  if (sort) {
    matchedEntries = sort->sortFile(sortType, matchedEntries);
  }
  saveLogEntriesAsJson(matchedEntries, path, newDataEntry.getFileName());
}
