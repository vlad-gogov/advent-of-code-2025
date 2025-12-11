add_executable(day11 main.cpp)
configure_file(input.txt input.txt COPYONLY)
target_link_libraries(day11 aoc_common)
