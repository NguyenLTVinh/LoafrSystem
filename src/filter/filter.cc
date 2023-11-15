#include "logentry.h"

// Implementation of the LogEntry constructor
Filter::Filter(const std::string& time, const std::string& comp, const std::string& event,
                   const std::string& field, int value)
    : timeStamp(time),
      componentName(comp),
      eventType(event),
      dataFieldName(field),
      dataValue(value) {}

Filter:: Filter(const vector<std::string>& logEntries, const std::string&, const std::string& operator, const int val);
