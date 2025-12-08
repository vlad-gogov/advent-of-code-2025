add_executable(day08 main.cpp)
configure_file(input.txt input.txt COPYONLY)
target_link_libraries(day08 aoc_common)
