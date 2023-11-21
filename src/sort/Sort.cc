#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

const std::vector<std::string>& Sort::sortFile(
    const std::string& sortType, std::vector<std::string>& logEntries) {
  if (logEntries.empty()) {
    std::cerr << "Error: Log entries are empty. ";
    return logEntries;
  }

  auto compareTimeStamp = [] {
    (const std::string& logEntry1, const std::string& logEntry2)
  } {
    std::istringstream iss1(logEntry1), iss2(logEntry2);

    std::string timestamp1, timestamp2;
    std::getline(iss1, timestamp1, ',');
    std::getline(iss2, timestamp2, ',');

    return timestamp1 < timestamp2;
  };

  if (sortType == "ascending") {
    std::sort(logEntries.begin(), logEntries.end(), compareTimestamp);
  } else if (sortType == "descending") {
    std::sort(logEntries.rbegin(), logEntries.rend(), compareTimestamp);
  } else {
    std::cerr << "Error: Invalid sort type. Use 'ascending' or 'descending'.\n";
  }

  return logEntries;
}