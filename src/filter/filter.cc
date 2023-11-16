#include "Filter.h"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

Filter::Filter() {}

Filter::Filter(const std::string& time, const std::string& comp, const std::string& event,
               const std::string& field, int value)
    : timeStamp(time),
      componentName(comp),
      eventType(event),
      dataFieldName(field),
      dataValue(value) {}

std::vector<std::string> Filter::FilterLog(const std::vector<std::string>& logEntries, 
                                           const std::string& logItem, 
                                           const std::string& operation, 
                                           const int val) {
    std::vector<std::string> matchedEntries;
    for (const auto& entry : logEntries) {
        std::istringstream iss(entry);
        std::vector<std::string> entryItems;
        std::string item;

        while (std::getline(iss, item, ',')) {
            entryItems.push_back(item);
        }

        if (!entryItems.empty()) {
            try {
                int logItemInteger = std::stoi(entryItems.back());
                if ((operation == "<" && val > logItemInteger) ||
                    (operation == "=" && val == logItemInteger) ||
                    (operation == ">" && val < logItemInteger)) {
                    matchedEntries.push_back(entry);
                }
            } catch (std::invalid_argument& e) {
                std::cerr << "Non-integer value in Data Value field.\n";
            }
        }
    }
    return matchedEntries;
}
