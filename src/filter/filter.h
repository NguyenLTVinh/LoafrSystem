#ifndef FILTER_H
#define FILTER_H

#include <string>
#include <vector>

class Filter {
 private:
  std::string timeStamp;
  std::string componentName;
  std::string eventType;
  std::string dataFieldName;
  int dataValue;

 public:
  Filter();

  Filter(const std::string& time, const std::string& comp,
         const std::string& event, const std::string& field, int value);

  std::vector<std::string> FilterLog(const std::vector<std::string>& logEntries,
                                     const std::string& logItem,
                                     const std::string& operation,
                                     const int val);
};

#endif
