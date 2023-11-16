#ifndef NEWDATAENTRY_H
#define NEWDATAENTRY_H

#include <string>
#include <vector>

class NewDataEntry {
 private:
  std::string fileName;
  std::string path;
  std::vector<std::string> data;

 public:
  NewDataEntry(const std::string& fileName, const std::string& path);
  void loadData();
  const std::string& getFileName() const;
  const std::string& getPath() const;
  const std::vector<std::string>& getData() const;
};

#endif  // NEWDATAENTRY_H
