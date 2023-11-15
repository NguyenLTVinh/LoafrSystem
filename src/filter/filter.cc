#include "logentry.h"

// Implementation of the LogEntry constructor
LogEntry::LogEntry(const std::string& time, const std::string& comp, const std::string& event,
                   const std::string& field, int value)
    : timeStamp(time),
      componentName(comp),
      eventType(event),
      dataFieldName(field),
      dataValue(value) {}
