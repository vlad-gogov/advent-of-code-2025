#include <cctype>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "common/util.hpp"

constexpr const char *input_file = "input.txt";

struct TraceBeam {
  std::vector<std::vector<bool>> visited;
  size_t answer{0};

  TraceBeam(size_t rows, size_t cols)
      : visited(rows, std::vector<bool>(cols, false)) {}

  void solve(const std::vector<std::string> &rows, int row, int col) {
    if (row + 1 >= rows.size() || col > rows[0].size() || col < 0) {
      return;
    }
    if (visited[row][col]) {
      return;
    }
    visited[row][col] = true;
    char below = rows[row + 1][col];
    if (below == '^') {
      answer++;
      int left = col - 1;
      int right = col + 1;
      int new_row = row + 1;
      if (left >= 0) {
        solve(rows, new_row, left);
      }
      if (right < rows[0].size()) {
        solve(rows, new_row, right);
      }
      return;
    }
    solve(rows, row + 1, col);
  }
};

struct CountPath {
  std::vector<std::vector<uint64_t>> dp;
  std::vector<std::vector<bool>> visited;

  CountPath(size_t rows = 0, size_t cols = 0)
      : dp(rows, std::vector<uint64_t>(cols, 0)),
        visited(rows, std::vector<bool>(cols, false)) {}

  size_t solve(const std::vector<std::string> &rows, int row, int col) {
    if (row < 0 || col < 0 || col >= rows[0].size() || row >= rows.size()) {
      return 0;
    }
    if (row + 1 == rows.size()) {
      return 1;
    }

    if (visited[row][col]) {
      return dp[row][col];
    }

    visited[row][col] = true;
    char below = rows[row + 1][col];

    if (below == '^') {
      dp[row][col] =
          solve(rows, row + 1, col - 1) + solve(rows, row + 1, col + 1);
    } else {
      dp[row][col] = solve(rows, row + 1, col);
    }

    return dp[row][col];
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  [[maybe_unused]] size_t line_count = count_lines(input_file);

  std::ifstream file(input_file);
  // Redirect standard input to read from the file
  if (file) {
    std::cin.rdbuf(file.rdbuf());
  }

  std::vector<std::string> rows;
  std::string line;
  while (std::cin >> line) {
    rows.push_back(line);
  }
  size_t pos_start = rows[0].find('S');

  TraceBeam trace_beam(rows.size(), rows[0].size());
  trace_beam.solve(rows, 0, pos_start);
  std::cout << "Part 1: " << trace_beam.answer << std::endl;

  CountPath count_path(rows.size(),
                       rows[0].size()); // Correct answer: 1667
  std::cout << "Part 2: " << count_path.solve(rows, 0, pos_start)
            << std::endl; // Correct answer: 62943905501815
  return 0;
}
