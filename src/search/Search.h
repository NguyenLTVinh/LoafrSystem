#ifndef SEARCH_H
#define SEARCH_H

#include <string>
#include <vector>

class Search {
 public:
  std::vector<std::string> searchKeyword(
      const std::string& keyword, const std::vector<std::string>& logEntries);
};

#endif