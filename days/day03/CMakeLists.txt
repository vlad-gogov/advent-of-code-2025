add_executable(day03 main.cpp)
configure_file(input.txt input.txt COPYONLY)
target_link_libraries(day03 aoc_common)
