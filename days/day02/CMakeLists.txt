add_executable(day02 main.cpp)
configure_file(input.txt input.txt COPYONLY)
target_link_libraries(day02 aoc_common)
