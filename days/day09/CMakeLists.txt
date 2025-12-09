add_executable(day09 main.cpp)
configure_file(input.txt input.txt COPYONLY)
target_link_libraries(day09 aoc_common)
