#ifndef LOAFRMODEL_H
#define LOAFRMODEL_H

#include <string>
#include <vector>

class LoafrModel {
private:
    std::vector<std::string> logEntries;

public:
    LoafrModel();
    void loadLogFile(const std::string& filePath, const std::string& fileName);
    const std::vector<std::string>& getLogEntries() const;
};

#endif
