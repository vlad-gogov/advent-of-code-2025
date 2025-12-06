#!/bin/bash

if [ -z "$1" ]; then
    echo "Usage: $0 <day-name>"
    exit 1
fi

NAME="$1"
DIR="days/$NAME"

mkdir -p "$DIR"

# main.cpp template
cat > "$DIR/main.cpp" <<EOF
#include <cstdint>
#include <fstream>
#include <iostream>
#include <cmath>

#include "common/util.hpp"

constexpr const char* input_file = "input.txt";

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  [[maybe_unused]] size_t line_count = count_lines(input_file);

  std::ifstream file(input_file);
  // Redirect standard input to read from the file
  if (file) {
    std::cin.rdbuf(file.rdbuf());
  }
  size_t result_part1 = 0;
  size_t result_part2 = 0;

  

  std::cout << "Part 1: " << result_part1 << std::endl;
  std::cout << "Part 2: " << result_part2 << std::endl;
  return 0;
}
EOF

# CMakeLists.txt
cat > "$DIR/CMakeLists.txt" <<EOF
add_executable(${NAME} main.cpp)
configure_file(input.txt input.txt COPYONLY)
target_link_libraries(${NAME} aoc_common)
EOF

# input
touch "$DIR/input.txt"

echo "Created $DIR"
