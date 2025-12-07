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

struct TraceBeamCfg {
  std::set<std::pair<size_t, size_t>> visited;
  size_t answer{0};
};

void traceBeam(const std::vector<std::string> &rows, TraceBeamCfg &cfg, int row,
               int col) {
  if (row + 1 >= rows.size() || col > rows[0].size() || col < 0) {
    return;
  }
  if (cfg.visited.contains({row, col})) {
    return;
  }
  cfg.visited.insert({row, col});
  char below = rows[row + 1][col];
  if (below == '^') {
    cfg.answer++;
    int left = col - 1;
    int right = col + 1;
    int new_row = row + 1;
    if (left >= 0) {
      traceBeam(rows, cfg, new_row, left);
    }
    if (right < rows[0].size()) {
      traceBeam(rows, cfg, new_row, right);
    }
    return;
  }
  traceBeam(rows, cfg, row + 1, col);
}

struct CountPathCfg {
  std::vector<std::vector<uint64_t>> dp;
  std::vector<std::vector<bool>> dp_visited;

  CountPathCfg(size_t rows = 0, size_t cols = 0)
      : dp(rows, std::vector<uint64_t>(cols, 0)),
        dp_visited(rows, std::vector<bool>(cols, false)) {}
};

size_t countPath(const std::vector<std::string> &rows, CountPathCfg &cfg,
                 int row, int col) {
  if (row < 0 || col < 0 || col >= rows[0].size() || row >= rows.size()) {
    return 0;
  }
  if (row + 1 == rows.size()) {
    return 1;
  }

  if (cfg.dp_visited[row][col]) {
    return cfg.dp[row][col];
  }

  cfg.dp_visited[row][col] = true;
  char below = rows[row + 1][col];

  if (below == '^') {
    cfg.dp[row][col] = countPath(rows, cfg, row + 1, col - 1) +
                       countPath(rows, cfg, row + 1, col + 1);
  } else {
    cfg.dp[row][col] = countPath(rows, cfg, row + 1, col);
  }

  return cfg.dp[row][col];
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

  std::vector<std::string> rows;
  std::string line;
  while (std::cin >> line) {
    rows.push_back(line);
  }
  size_t pos_start = rows[0].find('S');

  TraceBeamCfg trace_cfg;
  traceBeam(rows, trace_cfg, 0, pos_start);
  std::cout << "Part 1: " << trace_cfg.answer << std::endl;

  CountPathCfg count_cfg(rows.size(),
                         rows[0].size()); // Correct answer: 1667
  std::cout << "Part 2: " << countPath(rows, count_cfg, 0, pos_start)
            << std::endl; // Correct answer: 62943905501815
  return 0;
}
