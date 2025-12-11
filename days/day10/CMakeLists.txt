find_path(Z3_INCLUDE_DIR NAMES z3++.h)
find_library(Z3_LIBRARY NAMES z3)

if (NOT Z3_INCLUDE_DIR OR NOT Z3_LIBRARY)
  message(WARNING "Z3 library not found. Please install Z3 and try again.")
  return()
endif()

add_executable(day10 main.cpp)
configure_file(input.txt input.txt COPYONLY)
target_include_directories(day10 PRIVATE ${Z3_INCLUDE_DIR})
target_link_libraries(day10 aoc_common ${Z3_LIBRARY})
