# LoafrSystem Version 0.1

### Overview

This document provides instructions on building, executing, and testing the Loafr system, version 0.1. The Loafr system is designed to read log files, execute analyses, and produce output based on user-defined search, sort, and filter criteria.

## Table of Contents

1. Getting Started
   - Prerequisites
2. Building the Project
   - Manually
   - Scripts
3. Executing the Program
   - Command Line Interface
   - Example Usage
   - Example Input and Outputs
4. Unit Tests
   - Running Unit Tests
5. Doxygen Documentation
   - Viewing Documenation
6. Product Backlog

### Getting Started

Before utilizing the Loafr System, ensure that you have the following prerequisites installed:

- GCC 9.3 or Clang 10
- CMake 3.20 or higher
- Linux or macOS Operating System

### Building the Project

- All commands should be run in the app directory !!!

- To build the project manually run this command.

```
mkdir build && cd build && cmake ../ && make && cd ..
```

This'll generate and run the make file for the project, leaving the loafr executable, and the loafr_test executable.
These executables run the project, and run the testing suite respectively.

- Another option is to run the build script. First you'll need to make this file executable with chmod +x scripts/build.sh.
  Then you can run the script using scripts/build.sh (Must be in the app directory).

- To clean the build directory and executables generated by the script and start fresh, use the clean script.
  You'll also need to make this file executable with chmod +x scripts/clean.sh.
  Then you can run the script using scripts/clean.sh. (Must be in the app directory)

### Executing the program

- Command Line Interface
- The Loafr program provides a command-line interface with the following commands:

- load /path/to/file: Loads the log file specified in the path.
- out /path/to/outfolder: Sets the path to the output folder where results will be saved.
- filter-value fieldname operator value: Filters log entries based on the specified field, operator, and value.
- filter-event start_event end_event: Filter log entries between the start and end events.
- search keyword: Searches for log entries containing the specified keyword.
- sort order: Sorts log entries based on ascending or descending order.
- advance-filter start_event end_event fieldname operator value: Filter all entries between a start and end event and filter remaining entries based on specified field, operator, and value.
- Type quit to exit the program.

### Example Usage

- ./loafr
- load ../testlogs/2023-11-14-1.txt
- out ../testlogs
- filter-value sugar-level < 130
- filter-event glucose-monitor-report-start glucose-monitor-report-end
- search insulin pump
- sort ascending
- advance-filter glucose-monitor-report-start glucose-monitor-report-end sugar-level < 130
- quit

### Example Inputs and Outputs
- In LoafrSystem/testlogs/, there are various test log files that was generated by the python script in the same folder.
- By loading these files, the user can test the functionalities of Loafr.
- Example outputs are also present in the folder. Below is the commands used in the Loafr CLI to produce such outputs.
```
% load ../../testlogs/2023-11-14-1.txt
Loaded ../../testlogs/2023-11-14-1.txt
% out ../../testlogs
Output Folder Path Set To: ../../testlogs
% filter sugar-level < 120
% search insulin pump
% sort ascending
% sort descending
% quit
```

### Unit Test
- This project uses Google Test framework for writing and executing unit tests.
- The unit test suites are in the tests directory.
- As mentioned above, the loafr_test executable is generated when the project is built with the command:
```
mkdir build && cd build && cmake ../ && make && cd ..
```
- To run the loafr_test executable, cd into build directory, and run ./loafr_test in the terminal.

### Doxygen Documentation
- This project ultilizes Doxygen for documentations.
- To view the project's documentations, open LoafrSystem/docs/html/index.html

### Backlog
- Both the product backlog and the scrum backlog can be accessed in the Projects tab.
