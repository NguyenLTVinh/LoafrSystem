#include "LoafrModel.h"
#include <iostream>
// For testing Model translating txt files to vector.
int main() {
    LoafrModel model;
    model.loadLogFile("../test log files generator", "2023-11-14-1.txt");

    for (const auto& entry : model.getLogEntries()) {
        std::cout << entry << std::endl;
    }

    return 0;
}