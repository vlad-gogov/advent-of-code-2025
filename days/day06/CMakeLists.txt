add_executable(day06 main.cpp)
configure_file(input.txt input.txt COPYONLY)
target_link_libraries(day06 aoc_common)
