#ifndef NEWDATAENTRY_H
#define NEWDATAENTRY_H

#include <string>
#include <vector>

/**
 * @brief Represents a data entry that loads and stores data.
 */
class NewDataEntry {
 private:
  std::string fileName;
  std::string path;
  std::vector<std::string> data;

 public:
  /**
   * @brief Constructs a NewDataEntry object with the specified file name and
   * path.
   * @param fileName The name of the file.
   * @param path The path to the file.
   */
  NewDataEntry(const std::string& fileName, const std::string& path);

  /**
   * @brief Loads data from the file specified in the constructor.
   */
  void loadData();

  /**
   * @brief Gets the file name.
   * @return A constant reference to the file name.
   */
  const std::string& getFileName() const;

  /**
   * @brief Gets the file path.
   * @return A constant reference to the file path.
   */
  const std::string& getPath() const;

  /**
   * @brief Gets the loaded data from the file.
   * @return A constant reference to the vector of loaded data.
   */
  const std::vector<std::string>& getData() const;
};

#endif  // NEWDATAENTRY_H
