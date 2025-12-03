#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <stack>

#include "common/util.hpp"

constexpr const char* input_file = "input.txt";

std::size_t maxSeq(const std::vector<std::uint64_t>& digits, const std::size_t len_seq) {
  if (digits.size() < len_seq) {
    return 0;
  }

  std::int64_t need_remove = digits.size() - len_seq;
  std::stack<std::uint64_t> s;

  for (std::size_t i = 0; i < digits.size(); ++i) {
    while(!s.empty() && s.top() < digits[i] && need_remove > 0) {
      s.pop();
      --need_remove;
    }
    if (s.size() < len_seq) {
      s.push(digits[i]);
    } else if (need_remove > 0) {
      --need_remove;
    }
  }
  std::size_t sum = 0;
  std::size_t pow = 0;
  while (!s.empty()) {
    sum += s.top() * static_cast<std::uint64_t>(std::pow(10, pow++));
    s.pop();
  }
  return sum;
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

  std::size_t result_part1 = 0;
  std::size_t result_part2 = 0;

  std::string line;
  while (std::cin >> line) {
    if (line.empty() || line.size() < 2) {
      continue;
    }

    std::vector<std::uint64_t> digits(line.size());
    for (std::size_t i = 0; i < line.size(); ++i) {
      digits[i] = line[i] - '0';
    }

    result_part1 += maxSeq(digits, 2);
    result_part2 += maxSeq(digits, 12);
  }

  std::cout << "Part 1: " << result_part1 << std::endl; // Correct answer 17095
  std::cout << "Part 2: " << result_part2
            << std::endl; // Correct answer 168794698570517

  return 0;
}
