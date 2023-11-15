#include "logentry.h"

// Implementation of the LogEntry constructor
Filter::Filter(const std::string& time, const std::string& comp, const std::string& event,
                   const std::string& field, int value)
    : timeStamp(time),
      componentName(comp),
      eventType(event),
      dataFieldName(field),
      dataValue(value) {}


Filter::FilterLog(const vector<std::string>& logEntries, const std::string& logItem, const std::string& operator, const int val){

  std::vector<std::string> matchedEntries;

  for (const auto& entry : logEntries) {
    // Need to check
      std::vector<std::string> entryItems;
      char *token = strtok(entry, ",")
      while (token != NULL){
        entryItems.push_back(entryItems);
        token = strtok(NULL, ",")
      }

      int logItemInteger = stoi(entryItems.back());
      if (entry.find(logItem) != std::string::npos) {
          if (operator == "<"){
              if (val < logItemInteger){
                matchedEntries.push_back(entry);
              }
          }
          if (operator == "="){
              if (val == logItemInteger){
                matchedEntries.push_back(entry);
              }
          }
          if (operator == ">") {
              if (val > logItemInteger){
                matchedEntries.push_back(entry);
              }
          }
          // May need to add more cases, ">=", "<="
          else {
            return "error";
          }
        }
    }
    return matchedEntries;
}
