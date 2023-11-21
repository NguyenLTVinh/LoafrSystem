#include "filter.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

Filter::Filter() {}

std::vector<std::string> Filter::FilterLog(
    const std::vector<std::string>& logEntries, const std::string& logItem,
    const std::string& operation, const int val) {
    std::vector<std::string> matchedEntries;
// Iterates through the logFile and adds all of the entries that contain the
// 'logItem' keyword and satisfy the operation to 'matchedEntries'
    for (const auto& entry : logEntries) {
        if (entry.find(logItem) != std::string::npos) {
            std::istringstream iss(entry);
            std::vector<std::string> entryItems;
            std::string item;

            while (std::getline(iss, item, ',')) {
                entryItems.push_back(item);
            }

            if (!entryItems.empty()) {
                try {
                    int logItemValue = std::stoi(entryItems.back());
                    if ((operation == "<" && logItemValue < val) ||
                        (operation == "=" && logItemValue == val) ||
                        (operation == ">" && logItemValue > val)) {
                        matchedEntries.push_back(entry);
                    }
                } catch (const std::invalid_argument&) {
                    std::cerr << "Invalid value for comparison in the last column of the entry.\n";
                }
            }
        }
    }

    if (matchedEntries.empty()) {
        std::cerr << "No entries matched the filter criteria.\n";
    }

    return matchedEntries;
}