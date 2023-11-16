// NewDataEntry.cc

#include "NewDataEntry.h"
#include <iostream>
#include <fstream>

NewDataEntry::NewDataEntry(const std::string& fileName, const std::string& path) 
    : fileName(fileName), path(path) {
      this->loadData();
}

void NewDataEntry::loadData() {
    std::string fullPath = path + "/" + fileName;
    std::ifstream file(fullPath);
    std::string line;

    if (file.is_open()) {
        std::cout << "Loaded " << fullPath << std::endl;
        data.clear();
        while (getline(file, line)) {
            data.push_back(line);
        }
        file.close();
    } else {
        std::cerr << "Unable to open file: " << fullPath << std::endl;
    }
}

const std::string& NewDataEntry::getFileName() const {
    return fileName;
}

const std::string& NewDataEntry::getPath() const {
    return path;
}

const std::vector<std::string>& NewDataEntry::getData() const {
    return data;
}
