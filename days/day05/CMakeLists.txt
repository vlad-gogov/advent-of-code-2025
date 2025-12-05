add_executable(day05 main.cpp)
configure_file(input.txt input.txt COPYONLY)
target_link_libraries(day05 aoc_common)
