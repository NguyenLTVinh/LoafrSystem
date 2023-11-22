#include "NewDataEntry.h"

#include <fstream>
#include <iostream>

/**
 * @brief Constructs a NewDataEntry object with file name and
 * path. It also loads data from the file.
 * @param fileName The name of the file.
 * @param path The path to the file.
 */
NewDataEntry::NewDataEntry(const std::string& fileName, const std::string& path)
    : fileName(fileName), path(path) {
  this->loadData();
}

/**
 * @brief Loads data from the file specified in the constructor.
 * Clears the existing data and reads lines from the file.
 */
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

/**
 * @brief Gets the file name.
 * @return A constant reference to the file name.
 */

const std::string& NewDataEntry::getFileName() const { return fileName; }

/**
 * @brief Gets the file path.
 * @return A constant reference to the file path.
 */
const std::string& NewDataEntry::getPath() const { return path; }

/**
 * @brief Gets the loaded data from the file.
 * @return A constant reference to the vector of loaded data.
 */
const std::vector<std::string>& NewDataEntry::getData() const { return data; }
