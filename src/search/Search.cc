#include "Search.h"
#include <algorithm>

std::vector<std::string> Search::searchKeyword(const std::string& keyword, const std::vector<std::string>& logEntries) {
    std::vector<std::string> matchedEntries;

    for (const auto& entry : logEntries) {
        if (entry.find(keyword) != std::string::npos) {
            matchedEntries.push_back(entry);
        }
    }

    return matchedEntries;
}