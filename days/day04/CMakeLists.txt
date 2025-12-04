add_executable(day04 main.cpp)
configure_file(input.txt input.txt COPYONLY)
target_link_libraries(day04 aoc_common)
