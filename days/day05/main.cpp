#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

#include "common/util.hpp"

constexpr const char *input_file = "input.txt";

using Range = std::pair<std::uint64_t, std::uint64_t>;

std::size_t countFreshFruits(const std::vector<Range> &ranges,
                             const std::vector<std::uint64_t> &fruits) {
  std::size_t result = 0;
  for (const auto &fruit : fruits) {
    for (const auto &range : ranges) {
      if (fruit >= range.first && fruit <= range.second) {
        result++;
        break;
      }
    }
  }
  return result;
}

std::size_t countTotalFreshIDs(const std::vector<Range> &ranges) {
  std::vector<Range> copied_ranges = ranges;
  std::sort(copied_ranges.begin(), copied_ranges.end());
  std::vector<std::pair<std::uint64_t, std::uint64_t>> merged;
  for (auto &r : copied_ranges) {
    if (merged.empty() || r.first > merged.back().second + 1) {
      merged.push_back(r);
    } else {
      merged.back().second = std::max(merged.back().second, r.second);
    }
  }
  return std::accumulate(merged.begin(), merged.end(), 0ULL,
                         [](std::uint64_t acc, const Range &r) {
                           return acc + (r.second - r.first + 1);
                         });
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

  std::vector<Range> ranges;
  std::string line;
  while (std::getline(std::cin, line)) {
    if (line.empty()) {
      break;
    }
    ranges.push_back(parse_range(line));
  }

  std::vector<std::uint64_t> fruits;
  std::uint64_t x = 0;
  while (std::cin >> x) {
    fruits.push_back(x);
  }

  std::cout << "Part 1: " << countFreshFruits(ranges, fruits)
            << "\n"; // Correct answer 517
  std::cout << "Part 2: " << countTotalFreshIDs(ranges)
            << "\n"; // Correct answer 336173027056994

  return 0;
}
