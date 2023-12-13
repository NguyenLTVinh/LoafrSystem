#include <iostream>
#include <sstream>
#include <string>

#include "LoafrModel.h"

void splitPath(const std::string &fullPath, std::string &dirPath,
               std::string &fileName) {
  size_t pos = fullPath.find_last_of("/\\");
  if (pos != std::string::npos) {
    dirPath = fullPath.substr(0, pos);
    fileName = fullPath.substr(pos + 1);
  } else {
    dirPath = ".";
    fileName = fullPath;
  }
}

int main() {
  LoafrModel model;
  std::unique_ptr<NewDataEntry> logData;
  std::string outputFolderPath =
      "./";  // Default output folder is current folder
  bool loadCalled = false;

  std::cout << "Loafr Command Line Interface\n";
  std::cout << "============================\n";
  std::cout << "Usage instructions:\n";
  std::cout << "1. load /path/to/file\n";
  std::cout << "   - Loads the log file specified in the path.\n";
  std::cout << "   - Example: load logs/logfile.txt\n\n";

  std::cout << "2. out /path/to/outfolder\n";
  std::cout << "   - Sets the path to the output folder where results will be "
               "saved.\n";
  std::cout << "   - Example: out results/\n\n";

  std::cout << "3. filter-value fieldname operator value\n";
  std::cout << "   - Filters log entries based on the specified field, "
               "operator, and value.\n";
  std::cout << "   - Supported operators: '=', '>', '<'\n";
  std::cout << "   - Example: filter sugar-level > 130\n\n";

  std::cout << "4. filter-event start_event end_event\n";
  std::cout << "   - Filters log entries between start and end events.\n";
  std::cout << "   - Example: filter event StartEvent EndEvent\n\n";

  std::cout << "5. search keyword\n";
  std::cout
      << "   - Searches for log entries containing the specified keyword.\n";
  std::cout << "   - Example: search insulin pump\n\n";

  std::cout << "6. sort order\n";
  std::cout
      << "   - Sorts for log entries by time stamps based on ascending or "
         "descending order.\n";
  std::cout << "   - Supported orders: 'ascending', 'descending'\n";
  std::cout << "   - Example: sort descending\n\n";

  std::cout
      << "7. advance-filter start_event end_event fieldname operator value\n";
  std::cout << "   - Advanced filtering: First filters log entries between "
               "start and end events, then filters these entries based on the "
               "specified field, operator, and value.\n";
  std::cout << "   - Example: advance-filter StartEvent EndEvent sugar-level > "
               "130\n\n";

  std::cout << "Type 'quit' to exit the program.\n";
  std::cout << "============================\n";

  std::string line;
  while (true) {
    std::cout << "% ";
    std::getline(std::cin, line);

    if (line == "quit") {
      break;
    }

    std::istringstream iss(line);
    std::string command;
    iss >> command;
    // TODO: make changes to accomodate loading just a path.
    if (command == "load") {
      std::string logFilePath, path, fileName;
      iss >> logFilePath;
      splitPath(logFilePath, path, fileName);
      logData = std::make_unique<NewDataEntry>(fileName, path);
      loadCalled = true;
    } else if (command == "out") {
      std::string path;
      iss >> path;
      outputFolderPath = path;
      std::cout << "Output Folder Path Set To: " << outputFolderPath
                << std::endl;
    } else if (command == "filter-value") {
      if (loadCalled) {
        std::string field, compare, valueStr;
        int value;
        iss >> field >> compare >> valueStr;
        try {
          value = std::stoi(valueStr);
          model.SaveFilterLog(*logData, field, compare, value,
                              outputFolderPath);
        } catch (std::invalid_argument) {
          std::cout << "Error Invalid Argument: Make sure to pass in a opeator "
                       "and a number to filter "
                       "by, otherwise use search"
                    << std::endl;
        }
      } else {
        std::cout << "No Log Files Loaded\n" << std::endl;
      }
    } else if (command == "filter-event") {
      if (loadCalled) {
        std::string startName, endName;
        iss >> startName >> endName;
        try {
          model.saveFilterByStartEndEventsToLog(*logData, startName, endName,
                                                outputFolderPath);
        } catch (std::invalid_argument) {
          std::cout << "Wrong inputs" << std::endl;
        }
      }
    } else if (command == "advance-filter") {
      if (loadCalled) {
        std::string startEvent, endEvent, field, operatorStr, valueStr;
        int value;
        iss >> startEvent >> endEvent >> field >> operatorStr >> valueStr;
        try {
          value = std::stoi(valueStr);
          model.saveAdvancedFilter(*logData, startEvent, endEvent, field,
                                   operatorStr, value, outputFolderPath);
        } catch (std::invalid_argument) {
          std::cerr << "Error: Invalid argument for value. Please ensure it's "
                       "a number.\n";
        }
      } else {
        std::cerr << "No Log Files Loaded\n";
      }
    } else if (command == "search") {
      if (loadCalled) {
        std::string keyword;
        std::getline(iss, keyword);
        if (!keyword.empty() && keyword.front() == ' ') {
          keyword.erase(0, 1);
        }
        model.SaveSearchKeyword(keyword, *logData, outputFolderPath);
      } else {
        std::cout << "No Log Files Loaded\n" << std::endl;
      }
    } else if (command == "sort") {
      if (loadCalled) {
        std::string sortOrder;
        iss >> sortOrder;
        if (sortOrder == "ascending" || sortOrder == "descending") {
          model.sortFileByTimestamp(sortOrder, *logData, outputFolderPath);
        } else {
          std::cerr << "Invalid sort order. Please use 'ascending' or "
                       "'descending'.\n";
        }
      } else {
        std::cerr << "No Log Files Loaded\n";
      }
    } else {
      std::cerr << "Invalid command or insufficient arguments.\n";
    }
  }

  return 0;
}
