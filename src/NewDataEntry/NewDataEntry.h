#ifndef NEWDATAENTRY_H
#define NEWDATAENTRY_H

#include <string>
#include <vector>

class NewDataEntry {
public:
  std::string fileName;
  std::string Path;
  std::vector<std::byte> data;
};
#endif
