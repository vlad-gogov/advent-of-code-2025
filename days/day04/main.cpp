#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "common/util.hpp"

constexpr const char *input_file = "input.txt";

constexpr std::int8_t dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
constexpr std::int8_t dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

std::size_t countAccessibleRolls(const std::vector<std::string> &grid) {
  std::size_t count = 0;
  for (std::int64_t i = 0; i < grid.size(); i++) {
    for (std::int64_t j = 0; j < grid[i].size(); j++) {
      if (grid[i][j] != '@') {
        continue;
      }

      std::int64_t neighbors = 0;
      for (std::int64_t k = 0; k < 8; k++) {
        std::int64_t ni = i + dy[k];
        std::int64_t nj = j + dx[k];
        if (ni >= 0 && ni < grid.size() && nj >= 0 && nj < grid[i].size() &&
            grid[ni][nj] == '@') {
          neighbors++;
        }
      }
      count += (neighbors < 4);
    }
  }
  return count;
}

std::size_t countRemovableRolls(const std::vector<std::string> &grid) {
  std::vector<std::string> grid_copy = grid;
  std::size_t count = 0;
  while (true) {
    std::vector<std::pair<std::size_t, std::size_t>> to_remove;
    for (std::int64_t i = 0; i < grid_copy.size(); i++) {
      for (std::int64_t j = 0; j < grid_copy[i].size(); j++) {
        if (grid_copy[i][j] != '@') {
          continue;
        }

        std::int64_t neighbors = 0;
        for (std::int64_t k = 0; k < 8; k++) {
          std::int64_t ni = i + dy[k];
          std::int64_t nj = j + dx[k];
          if (ni >= 0 && ni < grid_copy.size() && nj >= 0 &&
              nj < grid_copy[i].size() && grid_copy[ni][nj] == '@') {
            neighbors++;
          }
        }
        if (neighbors < 4) {
          to_remove.emplace_back(i, j);
        }
      }
    }
    if (to_remove.empty()) {
      break;
    }
    for (const auto &[i, j] : to_remove) {
      grid_copy[i][j] = '.';
    }
    count += to_remove.size();
  }
  return count;
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

  std::vector<std::string> grid;
  std::string line;

  while (std::cin >> line) {
    grid.push_back(line);
  }

  std::cout << "Part 1: " << countAccessibleRolls(grid)
            << std::endl; // Correct answer 1416
  std::cout << "Part 2: " << countRemovableRolls(grid)
            << std::endl; // Correct answer 9086
  return 0;
}
