cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Project Name Verison
project(loafr VERSION 0.1)

#Include Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Include nlohmann/json
FetchContent_Declare(
  json
  URL https://github.com/nlohmann/json/releases/download/v3.10.4/json.tar.xz
)
FetchContent_MakeAvailable(json)

# Adding main.cc and other source files
add_executable(loafr main.cc src/LoafrModel.cc src/NewDataEntry.cc src/Search.cc src/Sort.cc src/filter.cc)

#Adding header files
target_include_directories(loafr PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(loafr PRIVATE nlohmann_json::nlohmann_json)
# Testing
enable_testing()

add_executable(
  loafr_test
  tests/LoafrModel_unittests.cc
)
target_include_directories(loafr_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(
  loafr_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(loafr_test)
