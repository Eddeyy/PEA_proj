cmake_minimum_required(VERSION 3.20)
project(TSP_BF)

set(CMAKE_CXX_STANDARD 14)
include_directories(${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/include/Algorithms)
add_subdirectory(src)

add_executable(TSP_BF src/main.cpp include/App.hpp src/App.cpp include/Algorithms/StratTSP.hpp include/Algorithms/BruteForceTSP.hpp src/Algorithms/BruteForceTSP.cpp src/Utilities.cpp include/Utilities.hpp)
