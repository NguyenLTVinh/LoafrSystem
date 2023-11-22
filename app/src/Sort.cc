#include "Sort.h"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

/**
 * @brief Constructor for the sort class.
 */
Sort::Sort() {}

/**
 * @brief Sorts the log entries based on a sort type if log entries contain
 * data, otherwise returns empty log entries.
 *
 * sortFile method sorts the log entries in either ascending or descending order
 * based on the specified sort type. It uses a lambda function to compare
 * timestamps for sorting.
 *
 * @param sortType The type of sorting (ascending or descending).
 * @param fileContents The vector containing the data being sorted.
 * @return std::vector<std::string> The sorted log entries.
 */
std::vector<std::string> Sort::sortFile(const std::string& sortType,
                                        std::vector<std::string>& logEntries) {
  if (logEntries.empty()) {
    std::cerr << "Error: Log entries are empty.\n";
    return logEntries;
  }

  // lamnda function that compares the timestamps
  auto compareTimestamp = [](const std::string& logEntry1,
                             const std::string& logEntry2) {
    std::istringstream iss1(logEntry1), iss2(logEntry2);

    std::string timestamp1, timestamp2;
    std::getline(iss1, timestamp1, ',');
    std::getline(iss2, timestamp2, ',');

    return timestamp1 < timestamp2;
  };

  // Sorting based on the specified type
  if (sortType == "ascending") {
    std::sort(logEntries.begin(), logEntries.end(), compareTimestamp);
  } else if (sortType == "descending") {
    std::sort(logEntries.begin(), logEntries.end(),
              [&compareTimestamp](const std::string& a, const std::string& b) {
                return compareTimestamp(b, a);
              });
  } else {
    std::cerr << "Error: Invalid sort type. Use 'ascending' or 'descending'.\n";
  }

  return logEntries;
}
