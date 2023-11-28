/**
 * @file Search.h
 * @brief Defines the Search class for searching keywords in log entries.
 */

#ifndef SEARCH_H
#define SEARCH_H

#include <string>
#include <vector>

/**
 * @class Search
 * @brief A class that provides functionality to search for a specific keyword
 * in log entries.
 *
 * The Search class offers a method to filter log entries based on the presence
 * of a specified keyword, returning all entries that contain this keyword.
 * This traces to section 3.3.9 Class: Search of the Design Document.
 */
class Search {
 public:
  /**
   * @brief Searches for a keyword in a collection of log entries.
   *
   * Iterates through log entries and selects those that contain the specified
   * keyword.
   *
   * @param keyword The keyword to search for in the log entries.
   * @param logEntries A vector of strings representing the log entries to be
   * searched.
   * @return A vector of strings containing log entries that match the keyword.
   */
  std::vector<std::string> searchKeyword(
      const std::string& keyword, const std::vector<std::string>& logEntries);
};

#endif  // SEARCH_H
