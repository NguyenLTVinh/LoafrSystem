#ifndef LOAFRMODEL_H
#define LOAFRMODEL_H

#include <string>
#include <vector>
#include "Search/Search.h"
#include "Filter/Filter.h"

class LoafrModel {
private:
    std::vector<std::string> logEntries;
    Filter* filter;
    Search* search;

public:
    LoafrModel();
    ~LoafrModel();
    void loadLogFile(const std::string& filePath, const std::string& fileName);
    const std::vector<std::string>& getLogEntries() const;
    void saveLogEntriesAsJson(const std::vector<std::string>& logEntries, const std::string& path);
    void SaveFilterLog(const std::vector<std::string>& logEntries, 
                                       const std::string& logItem, 
                                       const std::string& operation, 
                                       const int val, const std::string& path);
    void SaveSearchKeyword(const std::string& keyword, const std::vector<std::string>& logEntries, const std::string& path);
};

#endif
