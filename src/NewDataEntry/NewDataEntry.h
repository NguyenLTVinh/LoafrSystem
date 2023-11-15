#ifndef NEWDATAENTRY_H
#define NEWDATAENTRY_H

#include <string>
#include <vector>

class NewDataEntry {
private:
  std::string fileName;
  std::string path;
  std::vector<std::byte> data;

public:
  NewDataEntry(std::string fileName, std::string path,
               std::vector<std::byte> data);

  std::string getFileName();

  std::string getPath();

  std::vector<std::byte> getData();
};
#endif
