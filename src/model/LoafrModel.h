#ifndef LOAFRMODEL_H
#define LOAFRMODEL_H

#include <memory>

#include "filter/filter.h"
#include "NewDataEntry/NewDataEntry.h"
#include "search/Search.h"
#include "sort/Sort.h"

class LoafrModel {
 private:
  std::unique_ptr<Filter> filter;
  std::unique_ptr<Search> search;

 public:
  LoafrModel();
  ~LoafrModel() = default;
  void saveLogEntriesAsJson(const std::vector<std::string>& logEntries,
                            const std::string& path,
                            const std::string& baseFileName);
  void SaveFilterLog(const NewDataEntry& newDataEntry,
                     const std::string& logItem, const std::string& operation,
                     const int val, const std::string& path);
  void SaveSearchKeyword(const std::string& keyword,
                         const NewDataEntry& newDataEntry,
                         const std::string& path);
};

#endif  // LOAFRMODEL_H
