#ifndef FILTER_H
#define FILTER_H

#include <string>
#include <vector>


/**
 * @class Filter
 * @brief A class that provided the ability to filter certain logItems from a logfile
 * The filter class allows a user to input a keyword to match against as well as an integer to compare 
 * against the integers in the inputted logfiles. Only the logEntries that contain both the keyword and 
 * satisfy the operation will be returned.
 */
class Filter {
 public:
/**
 * @brief Filters the logitems by taking in a specifed logItem keyword and an operator to compare the logItem value to the given val in the parameters
 * 
 * @param logEntries A vector of strings representing all the entries in a logfile
 * @param logItem A string keyword that the filtered logEntries must all contain
 * @param operation A string operator, (i.e. '>', '<', or '=') to compare val and the logEntry values
 * @param val An int Value that will be compared against the logEntry values
 * @return A vector of strings representing all the filtered logItems
 */
  std::vector<std::string> FilterLog(const std::vector<std::string>& logEntries,
                                     const std::string& logItem,
                                     const std::string& operation,
                                     const int val);
};

#endif
