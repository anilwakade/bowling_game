cmake_minimum_required(VERSION 3.14)
project(BowlingGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Bowling game lib
add_library(BowlingGame STATIC BowlingGame.cpp)

# main app
add_executable(bowlingGameMain main.cpp)
target_link_libraries(bowlingGameMain BowlingGame)

# Add GoogleTest
enable_testing()
# Enable following line to see the detailed output of tests
# set(CMAKE_CTEST_ARGUMENTS "--verbose") 
find_package(GTest REQUIRED)
include(GoogleTest)

# "test" target to run unit tests
add_executable(testBowlingGame testBowlingGame.cpp)
target_link_libraries(testBowlingGame BowlingGame GTest::gtest GTest::gtest_main)
gtest_discover_tests(testBowlingGame)

# "run" target to run main app
add_custom_target(run
  COMMAND bowlingGameMain
  DEPENDS bowlingGameMain
  WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
