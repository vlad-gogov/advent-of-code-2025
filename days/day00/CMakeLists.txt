add_executable(day00 main.cpp)
configure_file(input.txt input.txt COPYONLY)
target_link_libraries(day00 aoc_common)
