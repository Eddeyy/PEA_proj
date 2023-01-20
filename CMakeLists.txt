cmake_minimum_required(VERSION 3.20)
project(TSP_BF)

set(CMAKE_CXX_STANDARD 14)
include_directories(${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/include/Algorithms)
add_subdirectory(src)

add_executable(
        TSP_BF

        src/main.cpp
        src/App.cpp
        src/Algorithms/BruteForceTSP.cpp
        src/Algorithms/HeldKarpTSP.cpp
        src/Algorithms/AntColonyOptimizationTSP.cpp
        src/Algorithms/SimulatedAnnealingTSP.cpp
        src/Algorithms/DAS.cpp
        src/Algorithms/QAS.cpp
        src/Utilities.cpp
)
