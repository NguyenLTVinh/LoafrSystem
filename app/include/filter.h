#ifndef FILTER_H
#define FILTER_H

#include <string>
#include <vector>

/**
 * @class Filter
 * @brief A class that provided the ability to filter certain logItems from a
 * logfile The filter class allows a user to input a keyword to match against as
 * well as an integer to compare against the integers in the inputted logfiles.
 * Only the logEntries that contain both the keyword and satisfy the operation
 * will be returned.
 * Traceability: This class is traced to Section 3.3.10: Filter Class on the
 * Design Document
 */
class Filter {
 public:
  /**
   * @brief Filters the logitems by taking in a specifed logItem keyword and an
   * operator to compare the logItem value to the given val in the parameters
   *
   * @param logEntries A vector of strings representing all the entries in a
   * logfile
   * @param logItem A string keyword that the filtered logEntries must all
   * contain
   * @param operation A string operator, (i.e. '>', '<', or '=') to compare val
   * and the logEntry values
   * @param val An int Value that will be compared against the logEntry values
   * @return A vector of strings representing all the filtered logItems
   */
  std::vector<std::string> FilterLog(const std::vector<std::string>& logEntries,
                                     const std::string& logItem,
                                     const std::string& operation,
                                     const int val);
  /**
   * @brief Filters log entries into groups based on start and end event names.
   *
   * This function takes a vector of log entries and two strings representing
   * the names of start and end events. It groups the log entries from each
   * start event to the subsequent end event. If a start event does not have a
   * corresponding end event, it includes all subsequent log entries until the
   * end of the logEntries vector. The function ensures that the values
   * associated with start and end events are -1 and prints an error to
   * std::cerr if they are not.
   *
   * @param logEntries A vector of strings, each representing a log entry.
   * @param StartEventName The name of the start event to look for in the log
   * entries.
   * @param EndEventName The name of the end event to look for in the log
   * entries.
   * @return A vector of string vectors, where each inner vector represents a
   * group of log entries from a start event to an end event. Returns an empty
   * vector if an error occurs (e.g., if the value associated with a start or
   * end event is not -1).
   *
   */
  std::vector<std::vector<std::string>> FilterByStartEndEvents(
      const std::vector<std::string>& logEntries,
      const std::string& StartEventName, const std::string& EndEventName);
};

#endif
