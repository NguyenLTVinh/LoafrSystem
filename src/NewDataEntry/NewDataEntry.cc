#include "NewDataEntry.h"

NewDataEntry::NewDataEntry(std::string fileName, std::string path,
                           std::vector<std::byte> data) {
  this->fileName = fileName;
  this->path = path;
  this->data = data;
}

std::string NewDataEntry::getFileName() { return this->fileName; }

std::string NewDataEntry::getPath() { return this->path; }

std::vector<std::byte> NewDataEntry::getData() { return this->data; }
