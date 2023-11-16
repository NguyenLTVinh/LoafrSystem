#include "Model/LoafrModel.h"
#include <iostream>
#include <string>
#include <sstream>

int main() {
    LoafrModel model;
    std::string outputFolderPath = "./"; // Default output folder is current folder
    bool loadCalled = false;

    std::cout << "Loafr Command Line Interface\n";
    std::cout << "============================\n";
    std::cout << "Usage instructions:\n";
    std::cout << "1. load /path/to/file\n";
    std::cout << "   - Loads the log file specified in the path.\n";
    std::cout << "   - Example: load logs/logfile.txt\n\n";

    std::cout << "2. out /path/to/outfolder\n";
    std::cout << "   - Sets the path to the output folder where results will be saved.\n";
    std::cout << "   - Example: out results/\n\n";

    std::cout << "3. filter fieldname operator value\n";
    std::cout << "   - Filters log entries based on the specified field, operator, and value.\n";
    std::cout << "   - Supported operators: '=', '>', '<'\n";
    std::cout << "   - Example: filter sugar-level > 130\n\n";

    std::cout << "4. search keyword\n";
    std::cout << "   - Searches for log entries containing the specified keyword.\n";
    std::cout << "   - Example: search insulin pump\n\n";

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

        if (command == "load") {
            std::string logFilePath;
            iss >> logFilePath;
            model.loadLogFile("", logFilePath);
            loadCalled = true;
        } 
        else if (command == "out") {
            std::string path;
            iss >> path;
            outputFolderPath = path;
            std::cout << "Output Folder Path Set To: " << outputFolderPath << std::endl;
        } 
        else if (command == "filter") {
            if (loadCalled) {
                std::string field, compare, valueStr;
                int value;
                iss >> field >> compare >> valueStr;
                value = std::stoi(valueStr);
                model.SaveFilterLog(model.getLogEntries(), field, compare, value, outputFolderPath);
            } else {
                std::cout << "No Log Files Loaded" << std::endl;
            }
            
        } 
        else if (command == "search") {
            if (loadCalled) {
                std::string keyword;
                std::getline(iss, keyword);
                if (!keyword.empty() && keyword.front() == ' ') {
                    keyword.erase(0, 1);
                }
                std::cout << "Searching for: " << keyword << std::endl;
                model.SaveSearchKeyword(keyword, model.getLogEntries(), outputFolderPath);
            } else {
                std::cout << "No Log Files Loaded" << std::endl;
            }
        } 
        else {
            std::cerr << "Invalid command or insufficient arguments.\n";
        }
    }

    return 0;
}
