#ifndef NEWDATAENTRY_H
#define NEWDATAENTRY_H

#include <string>
#include <vector>
<<<<<<< HEAD

class NewDataEntry {
public:
  std::string fileName;
  std::string Path;
  std::vector<std::byte> data;
=======
#include <cstddef>

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
>>>>>>> 3a598bc559db649d651fdb09d126d9a3b1fc1d84
};
#endif
