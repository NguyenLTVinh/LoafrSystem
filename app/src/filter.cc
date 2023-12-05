#include "filter.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> Filter::FilterLog(
    const std::vector<std::string>& logEntries, const std::string& logItem,
    const std::string& operation, const int val) {
  std::vector<std::string> matchedEntries;
  // Iterates through the logFile and adds all of the entries that contain the
  // 'logItem' keyword and satisfy the operation to 'matchedEntries'
  for (const auto& entry : logEntries) {
    if (entry.find(logItem) != std::string::npos) {
      std::istringstream iss(entry);
      std::vector<std::string> entryItems;
      std::string item;

      while (std::getline(iss, item, ',')) {
        entryItems.push_back(item);
      }

      if (!entryItems.empty()) {
        try {
          int logItemValue = std::stoi(entryItems.back());
          if ((operation == "<" && logItemValue < val) ||
              (operation == "=" && logItemValue == val) ||
              (operation == ">" && logItemValue > val)) {
            matchedEntries.push_back(entry);
          }
        } catch (const std::invalid_argument&) {
          std::cerr << "Invalid value for comparison in the last column of the "
                       "entry.\n";
        }
      }
    }
  }

  if (matchedEntries.empty()) {
    std::cerr << "No entries matched the filter criteria.\n";
  }

  return matchedEntries;
}

std::vector<std::vector<std::string>> Filter::FilterByStartEndEvents(
    const std::vector<std::string>& logEntries,
    const std::string& StartEventName, const std::string& EndEventName) {
  std::vector<std::vector<std::string>> groupedEntries;
  std::vector<std::string> currentGroup;
  bool isGrouping = false;

  for (const auto& entry : logEntries) {
    std::istringstream iss(entry);
    std::vector<std::string> entryItems;
    std::string item;
    while (std::getline(iss, item, ',')) {
      entryItems.push_back(item);
    }

    // Check for start event
    if (entryItems[2] == StartEventName) {
      if (entryItems[4] != "-1") {
        std::cerr << "Error: Start event value not -1" << std::endl;
        return std::vector<std::vector<std::string>>();  // Return empty vector
      }
      if (isGrouping) {
        // Handle previous group if it was not closed
        groupedEntries.push_back(currentGroup);
        currentGroup.clear();
      }
      isGrouping = true;
      currentGroup.push_back(entry);
    } else if (isGrouping && entryItems[2] == EndEventName) {
      if (entryItems[4] != "-1") {
        std::cerr << "Error: End event value not -1" << std::endl;
        return std::vector<std::vector<std::string>>();  // Return empty vector
      }
      currentGroup.push_back(entry);
      groupedEntries.push_back(currentGroup);
      currentGroup.clear();
      isGrouping = false;
    } else if (isGrouping) {
      currentGroup.push_back(entry);
    }
  }

  if (isGrouping) {
    // Handle last group if it was not closed
    groupedEntries.push_back(currentGroup);
  }

  return groupedEntries;
}