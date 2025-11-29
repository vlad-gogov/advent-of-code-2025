#include <cstdint>
#include <fstream>
#include <iostream>
#include <cmath>

#include <vector>

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

  size_t result = 0;
  std::vector<std::int64_t> first_list(line_count);
  std::vector<std::int64_t> second_list(line_count);

  for (size_t i = 0; i < line_count; ++i) {
    std::cin >> first_list[i] >> second_list[i];
  }

  std::sort(first_list.begin(), first_list.end());
  std::sort(second_list.begin(), second_list.end());

  for (size_t i = 0; i < line_count; ++i) {
    result += std::abs(first_list[i] - second_list[i]);
  }

  std::cout << result << std::endl;
  return 0;
}
