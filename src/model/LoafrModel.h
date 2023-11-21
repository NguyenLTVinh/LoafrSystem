/**
 * @file LoafrModel.h
 * @brief Defines the LoafrModel class for log file processing operations.
 */

#ifndef LOAFRMODEL_H
#define LOAFRMODEL_H

#include <memory>

#include "NewDataEntry/NewDataEntry.h"
#include "filter/filter.h"
#include "search/Search.h"
#include "sort/Sort.h"

/**
 * @class LoafrModel
 * @brief A model class that encapsulates filtering, searching, and sorting
 * functionalities for log entries.
 *
 * This class uses unique pointers to manage Filter, Search, and Sort objects,
 * providing a unified interface for processing log file entries.
 */
class LoafrModel {
 private:
  std::unique_ptr<Filter> filter;  ///< Unique pointer to a Filter object.
  std::unique_ptr<Search> search;  ///< Unique pointer to a Search object.
  std::unique_ptr<Sort> sort;      ///< Unique pointer to a Sort object.

 public:
  /**
   * @brief Constructs a new LoafrModel object.
   */
  LoafrModel();

  /**
   * @brief Default destructor.
   */
  ~LoafrModel() = default;

  /**
   * @brief Saves log entries as a JSON file.
   *
   * @param logEntries A vector of string containing log entries to be saved.
   * @param path The directory path where the JSON file will be saved.
   * @param baseFileName The base name of the file used to create the output
   * file name.
   */
  void saveLogEntriesAsJson(const std::vector<std::string>& logEntries,
                            const std::string& path,
                            const std::string& baseFileName);

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
  void SaveFilterLog(const NewDataEntry& newDataEntry,
                     const std::string& logItem, const std::string& operation,
                     const int val, const std::string& path);

  /**
   * @brief Searches for a keyword in log entries and saves the results as JSON.
   *
   * @param keyword The keyword to search for.
   * @param newDataEntry The NewDataEntry object containing log entries.
   * @param path The directory path where the search results JSON file will be
   * saved.
   */
  void SaveSearchKeyword(const std::string& keyword,
                         const NewDataEntry& newDataEntry,
                         const std::string& path);

  /**
   * @brief Sorts log entries by timestamp and saves them as JSON.
   *
   * @param sortType The type of sorting ("ascending" or "descending").
   * @param newDataEntry The NewDataEntry object containing log entries.
   * @param path The directory path where the sorted JSON file will be saved.
   */
  void sortFileByTimestamp(const std::string& sortType,
                           const NewDataEntry& newDataEntry,
                           const std::string& path);
};

#endif  // LOAFRMODEL_H
