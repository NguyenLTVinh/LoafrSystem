#include "Search.h"

#include <algorithm>
#include <iostream>

std::vector<std::string> Search::searchKeyword(
    const std::string& keyword, const std::vector<std::string>& logEntries) {
  std::vector<std::string> matchedEntries;
  if (keyword.empty()) {
    std::cerr << "Error: Keyword for search is empty.\n";
    return {};
  }

  for (const auto& entry : logEntries) {
    if (entry.find(keyword) != std::string::npos) {
      matchedEntries.push_back(entry);
    }
  }

  if (matchedEntries.empty()) {
    std::cerr << "No entries matched the search keyword: " << keyword << ".\n";
  }

  return matchedEntries;
}