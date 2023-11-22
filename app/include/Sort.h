#ifndef SORT_H
#define SORT_H

#include <string>
#include <vector>

class Sort {
private:

public:
    Sort();
    std::vector<std::string> sortFile(const std::string& sortType, std::vector<std::string>& fileContents) ;
    
};

#endif