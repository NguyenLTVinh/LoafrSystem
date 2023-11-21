# LoafrSystem Version 0.1

### #### Overview 
This document provides instructions on building, executing, and testing the Loafr system, version 0.1. The Loafr system is designed to read log files, execute analyses, and produce output based on user-defined search, sort, and filter criteria.

## Table of Contents 

1. Getting Started
- Prerequisites
2. Executing the Program
- Command Line Interface
- Example Usage
3. Unit Tests
- Running Unit Tests


### Getting Started
Before utilizing the Loafr System, ensure that you have the following prerequisites installed:

- C++ compiler
- CMake
- Nlohmann JSON Library: A C++ library for working with JSON data.  
    - To install the Nlohmann, follow the instruciton in the [official repository.](https://github.com/nlohmann/json)


### Executing the program 
- Command Line Interface
- The Loafr program provides a command-line interface with the following commands:

- load /path/to/file: Loads the log file specified in the path.
- out /path/to/outfolder: Sets the path to the output folder where results will be saved.
- filter fieldname operator value: Filters log entries based on the specified field, operator, and value.
- search keyword: Searches for log entries containing the specified keyword.
- sort keyword: Sorts log entries based on ascending or descending order.
- Type quit to exit the program.


# Example Usage 
./loafr
load ../testlogs/2023-11-14-1.txt
out ../testlogs
filter sugar-level < 130
search insulin pump
sort ascending
quit


### Unit Test 



