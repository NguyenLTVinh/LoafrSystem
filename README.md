# LoafrSystem
Project for CSCI 5801


logfile test info: Time stamp, Component Name, Event type, Data Field Name, Data Value


#ifndef FILTER_H
#define FILTER_H

#include <string>
#include <json/json.h>  // Assuming you have a JSON library, like jsoncpp

class Filter {
public:
    // Constructor
    Filter(const std::string& filePath);

    // Destructor
    ~Filter();

    // Method to filter the log file based on specified key and value
    Json::Value filterFile(const std::string& key, const std::string& value);

private:
    // Helper method to check if a line contains the specified key and value
    bool doesLineMatch(const std::string& line, const std::string& key, const std::string& value);

    // File path of the log file
    std::string filePath;

    // Read the contents of the file into a string
    std::string fileContents;
};

#endif // FILTER_H


#include "filter.h"
#include <fstream>
#include <sstream>
#include <iostream>

// Constructor
Filter::Filter(const std::string& filePath) : filePath(filePath) {
    // Read the contents of the file into a string
    std::ifstream inputFile(filePath);
    std::stringstream buffer;
    buffer << inputFile.rdbuf();
    fileContents = buffer.str();
}

// Destructor
Filter::~Filter() {
    // No explicit cleanup needed in this example
}

// Method to filter the log file based on specified key and value
Json::Value Filter::filterFile(const std::string& key, const std::string& value) {
    Json::Value result;

    // Split the file contents into lines
    std::istringstream fileStream(fileContents);
    std::string line;

    while (std::getline(fileStream, line)) {
        // Check if the line contains the specified key and value
        if (doesLineMatch(line, key, value)) {
            // If yes, add it to the result JSON object
            result["filtered_entries"].append(line);
        }
    }

    return result;
}

// Helper method to check if a line contains the specified key and value
bool Filter::doesLineMatch(const std::string& line, const std::string& key, const std::string& value) {
    // In this simple example, we check if the line contains both the key and value
    return (line.find(key) != std::string::npos) && (line.find(value) != std::string::npos);
}

