add_executable(day07 main.cpp)
configure_file(input.txt input.txt COPYONLY)
target_link_libraries(day07 aoc_common)
