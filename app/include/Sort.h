#ifndef SORT_H
#define SORT_H

#include <string>
#include <vector>

/**
 * @brief Sort class provides functionalities to sort the log files.
 * This class sorts log entries based on ascending or descending order of
 * timestamps.
 * This traces to section 3.3.8 Class: Sort of the Detailed Design Document.
 */
class Sort {
 private:
 public:
  /**
   * @brief Constructor for the sort class
   */
  Sort();

  /**
   * @brief Sorts log entries based on the specified sorting type.
   * @param sortType The type of sorting (ascending or descending).
   * @param fileContents The vector containing the data being sorted.
   * @return std::vector<std::string> The sorted log entries.
   */
  std::vector<std::string> sortFile(const std::string& sortType,
                                    std::vector<std::string>& fileContents);
};

#endif