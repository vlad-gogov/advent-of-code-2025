cmake_minimum_required(VERSION 3.16)
project(advent_of_code_2025 CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(common)

file(GLOB DAY_DIRS days/day*/)
foreach(day ${DAY_DIRS})
    if (EXISTS "${day}/CMakeLists.txt")
        add_subdirectory(${day})
    endif()
endforeach()
