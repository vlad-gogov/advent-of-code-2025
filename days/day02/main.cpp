#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>

#include "common/util.hpp"

constexpr const char *input_file = "input.txt";

bool isInvalidPart1(std::uint64_t x) {
  std::string s = std::to_string(x);
  std::size_t n = s.size();
  if (n % 2 != 0) {
    return false;
  }
  std::string a = s.substr(0, n / 2);
  std::string b = s.substr(n / 2, n);
  return a == b;
}

bool isInvalidPart2(std::uint64_t x) {
  std::string s = std::to_string(x);
  std::size_t n = s.size();
  for (std::uint64_t len = 1; len * 2 <= n; ++len) {
    if (n % len != 0) {
      continue;
    }
    std::string block = s.substr(0, len);
    bool result = true;

    for (std::uint64_t i = len; i < n; i += len) {
      if (s.substr(i, len) != block) {
        result = false;
        break;
      }
    }
    if (result) {
      return true;
    }
  }
  return false;
}

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
  std::string range;
  while (std::getline(file, range, ',')) {
    if (range.empty()) {
      continue;
    }
    std::size_t pos_dash = range.find('-');
    std::uint64_t L = stoull(range.substr(0, pos_dash));
    std::uint64_t R = stoull(range.substr(pos_dash + 1, range.size()));
    for (std::size_t x = L; x <= R; x++) {
      result_part1 += isInvalidPart1(x) ? x : 0;
      result_part2 += isInvalidPart2(x) ? x : 0;
    }
  }

  std::cout << "Part 1: " << result_part1 << std::endl; // Correct answer 23039913998
  std::cout << "Part 2: " << result_part2
            << std::endl; // Correct answer 35950619148
  return 0;
}
