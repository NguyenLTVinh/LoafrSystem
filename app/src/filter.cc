#include "filter.h"

#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

/**
 * @brief Filters log entries based on a specified keyword, numeric operation,
 *        and value.
 *
 * This function iterates through the provided log entries and filters them
 * based on the specified keyword, numeric operation, and value. The filtered
 * entries are returned as a vector of strings.
 *
 * @param logEntries A vector of strings representing all entries in a logfile.
 * @param logItem A string keyword that the filtered logEntries must contain.
 * @param operation A string operator ('>', '<', or '=') to compare val and
 *                  the logEntry values.
 * @param val An int Value that will be compared against the logEntry values.
 * @return A vector of strings representing all the filtered logItems.
 *
 */

std::vector<std::string> Filter::FilterLog(
    const std::vector<std::string> &logEntries, const std::string &logItem,
    const std::string &operation, const int val) {
  std::vector<std::string> matchedEntries;
  // Iterates through the logFile and adds all of the entries that contain the
  // 'logItem' keyword and satisfy the operation to 'matchedEntries'
  for (const auto &entry : logEntries) {
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
        } catch (const std::invalid_argument &) {
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

/**
 * @brief Groups log entries based on start and end events.
 *
 * This function groups log entries based on start and end events. It iterates
 * through the provided log entries, looking for start and end events, and
 * creates groups of entries between each start and end event pair. The grouped
 * entries are returned as a vector of vector of strings.
 *
 * @param logEntries A vector of strings, each representing a log entry.
 * @param StartEventName The name of the start event to look for in the log
 * entries.
 * @param EndEventName The name of the end event to look for in the log entries.
 * @return A vector of string vectors, where each inner vector represents a
 *         group of log entries from a start event to an end event.
 *         Returns an empty vector if an error occurs (if the value
 *         associated with a start or end event is not -1).
 *
 * Groups log entries into groups based on start and end event names.
 */
std::vector<std::vector<std::string>> Filter::FilterByStartEndEvents(
    const std::vector<std::string> &logEntries,
    const std::string &StartEventName, const std::string &EndEventName) {
  std::vector<std::vector<std::string>> groupedEntries;
  std::vector<std::string> currentGroup;
  bool isGrouping = false;

  for (const auto &entry : logEntries) {
    std::istringstream iss(entry);
    std::vector<std::string> entryItems;
    std::string item;
    while (std::getline(iss, item, ',')) {
      entryItems.push_back(item);
    }
    if (entryItems.size() == 0) {
      continue;
    }
    std::string trimmedStartEventName =
        std::regex_replace(StartEventName, std::regex(R"(\s*(.*?)\s*)"), "$1");
    std::string trimmedEndEventName =
        std::regex_replace(EndEventName, std::regex(R"(\s*(.*?)\s*)"), "$1");
    std::string trimmedEntryItem =
        std::regex_replace(entryItems[2], std::regex(R"(\s*(.*?)\s*)"), "$1");
    std::string trimmedValue =
        std::regex_replace(entryItems[4], std::regex(R"(\s*(.*?)\s*)"), "$1");
    // Check for start event
    if (trimmedEntryItem == trimmedStartEventName) {
      if (trimmedValue != "-1") {
        std::cerr << "Error: Start event value not -1" << std::endl;
        return std::vector<std::vector<std::string>>();  // Return empty vector
      }
      // if (isGrouping) {
      //   // Handle previous group if it was not closed
      //   groupedEntries.push_back(currentGroup);
      //   currentGroup.clear();
      // }
      isGrouping = true;
      currentGroup.push_back(entry);
    } else if (isGrouping && trimmedEntryItem == trimmedEndEventName) {
      if (trimmedValue != "-1") {
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
