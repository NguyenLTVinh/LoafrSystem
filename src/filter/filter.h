#ifndef FILTER_H
#define FILTER_H

#include <string>
#include <json/json.h> 
#include <vector>


class Filter {
    public: 
    std::string timeStamp;
    std::string componentName;
    std::string eventType;
    std::string dataFieldName;
    int dataValue;


    // Constructor for convenience
    Filter(const std::string& time, const std::string& comp, const std::string& event,
             const std::string& field, int value);
};
    Filter(const vector<std::string>& logEntries, const std::string&, const std::string& operator, const int val);

#endif