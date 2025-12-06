#include <cctype>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

#include "common/util.hpp"

constexpr const char* input_file = "input.txt";

std::vector<char> extractOperators(const std::string &line) {
  std::vector<char> operators;
  for (char c : line) {
    if (c == '+' || c == '*') {
      operators.push_back(c);
    }
  }
  return operators;
}

std::size_t computeColumnResult(const std::vector<std::uint64_t> &numbers, char op) {
  std::uint64_t result = (op == '*') ? 1 : 0;
  for (std::uint64_t num : numbers) {
    if (op == '+') {
      result += num;
    } else if (op == '*') {
      result *= num;
    }
  }
  return result;
}

std::size_t solveLeftToRight(const std::vector<std::string> &rows, std::size_t line_count) {
  std::vector<std::vector<std::uint64_t>> numbers(line_count - 1);
  for (std::size_t i = 0; i < line_count - 1; i++) {
    std::stringstream ss(rows[i]);
    std::uint64_t num;
    while (ss >> num) {
      numbers[i].push_back(num);
    }
  }
  std::vector<char> operators = extractOperators(rows[line_count - 1]);
  std::size_t result = 0;
  std::size_t cols = numbers[0].size();
  for (std::size_t i = 0; i < cols; i++) {
    std::vector<std::uint64_t> col_numbers(line_count - 1);
    for (std::size_t j = 0; j < line_count - 1; j++) {
      col_numbers[j] = numbers[j][i];
    }
    result += computeColumnResult(col_numbers, operators[i]);
  }
  return result;
}

bool isEmptyColumn(const std::vector<std::string> &rows, int col) {
  for (auto &r : rows)
    if (r[col] != ' ')
      return false;
  return true;
}

std::size_t solveRightToLeft(const std::vector<std::string> &rows,
                             std::size_t line_count) {
  std::size_t H = rows.size();
  std::size_t W = rows[0].size();
  std::vector<char> operators = extractOperators(rows[line_count - 1]);

  std::size_t result = 0;
  std::size_t operator_iter = 0;
  for (std::size_t i = 0; i < W; i++) {
    if (isEmptyColumn(rows, i)) {
      continue;
    }
    std::size_t block_left = i;
    std::size_t block_right = i + 1;
    while (block_right < W - 1 && !isEmptyColumn(rows, block_right + 1)) {
      block_right++;
    }
    std::vector<std::uint64_t> numbers(block_right - block_left + 1);
    for (std::size_t col = block_left; col <= block_right; col++) {
      std::string num;
      for (std::size_t row = 0; row < line_count - 1; row++) {
        char ch = rows[row][col];
        if (std::isdigit(ch)) {
          num.push_back(ch);
        }
      }
      if (!num.empty()) {
        numbers[col - block_left] = std::stoull(num);
      }
    }
    result += computeColumnResult(numbers, operators[operator_iter++]);
    i = block_right;
  }
  return result;
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
  while (std::getline(std::cin, line)) {
      rows.push_back(line);
  }

  std::cout << "Part 1: " << solveLeftToRight(rows, line_count)
            << std::endl; // Correct answer: 4076006202939
  std::cout << "Part 2: " << solveRightToLeft(rows, line_count)
            << std::endl; // Correct answer: 7903168391557

  return 0;
}
