#ifndef FILTER_H
#define FILTER_H

#include <string>
#include <json/json.h> 


class LogEntry {
    public: 
    std::string timeStamp;
    std::string componentName;
    std::string eventType;
    std::string dataFieldName;
    int dataValue;


    // Constructor for convenience
    LogEntry(const std::string& time, const std::string& comp, const std::string& event,
             const std::string& field, int value);
};

#endif