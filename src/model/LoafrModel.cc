#include "LoafrModel.h"
#include <iostream>
#include <fstream>

LoafrModel::LoafrModel() {}

void LoafrModel::loadLogFile(const std::string& filePath, const std::string& fileName) {
    std::string fullPath = filePath + "/" + fileName;
    std::ifstream file(fullPath);
    std::string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            logEntries.push_back(line);
        }
        file.close();
    } else {
        std::cerr << "Unable to open file: " << fullPath << std::endl;
    }
}

const std::vector<std::string>& LoafrModel::getLogEntries() const {
    return logEntries;
}