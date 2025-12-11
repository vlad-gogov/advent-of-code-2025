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

#include "z3++.h"

#include "common/util.hpp"

constexpr const char *input_file = "input.txt";

static std::vector<uint64_t> parse_indices(const std::string &str) {
  std::vector<uint64_t> res;
  size_t start = 0;
  size_t pos = str.find(',', start);
  while (pos != std::string::npos) {
    std::string number = str.substr(start, pos - start);
    res.push_back(std::stoull(number));
    start = pos + 1;
    pos = str.find(',', start);
  }
  std::string number = str.substr(start);
  res.push_back(std::stoull(number));
  return res;
}

size_t solve1(const std::vector<std::string> &schemas,
              const std::vector<std::vector<std::vector<uint64_t>>> &buttons) {
  size_t result = 0;
  for (size_t i = 0; i < schemas.size(); i++) {
    const auto &current_schema = schemas[i];
    const auto &current_buttons = buttons[i];
    uint64_t schema_state = 0;
    for (size_t i = 0; i < current_schema.size(); i++) {
      if (current_schema[i] == '#') {
        schema_state += (1 << i);
      }
    }

    std::vector<uint64_t> button_n(current_buttons.size());
    for (size_t i = 0; i < button_n.size(); i++) {
      for (const auto &elem : current_buttons[i]) {
        button_n[i] += (1 << elem);
      }
    }

    size_t score = current_buttons.size();
    for (size_t i = 0; i < (1 << current_buttons.size()); i++) {
      size_t current_state = 0;
      size_t button_press = 0;
      for (size_t j = 0; j < current_buttons.size(); j++) {
        if ((i >> j) % 2 == 1) {
          current_state ^= button_n[j];
          button_press += 1;
        }
      }
      if (current_state == schema_state) {
        score = std::min(score, button_press);
      }
    }
    result += score;
  }
  return result;
}

size_t solve2(
    const std::vector<std::vector<std::vector<uint64_t>>> &buttons,
    const std::vector<std::vector<uint64_t>> &joltages) {
  size_t result = 0;
  for (size_t i = 0; i < buttons.size(); i++) {
    const auto &current_buttons = buttons[i];
    const auto &current_joltage = joltages[i];
    z3::context c;
    std::vector<z3::expr> V;
    for (int i = 0; i < current_buttons.size(); i++) {
      V.push_back(c.int_const(("B" + std::to_string(i)).c_str()));
    }

    std::vector<z3::expr> EQ;
    for (size_t i = 0; i < current_joltage.size(); i++) {
      z3::expr sum_terms = c.int_val(0);
      for (size_t j = 0; j < current_buttons.size(); j++) {
        if (std::find(current_buttons[j].begin(), current_buttons[j].end(),
                      i) != current_buttons[j].end()) {
          sum_terms = sum_terms + V[j];
        }
      }
      EQ.push_back(sum_terms == static_cast<int>(current_joltage[i]));
    }

    z3::optimize opt(c);
    z3::expr total_sum = c.int_val(0);
    for (const auto &v : V) {
      total_sum = total_sum + v;
    }
    opt.minimize(total_sum);
    for (auto &eq : EQ) {
      opt.add(eq);
    }
    for (auto &v : V) {
      opt.add(v >= 0);
    }
    if (opt.check() == z3::sat) {
      z3::model M = opt.get_model();
      for (auto &v : V) {
        int val = M.eval(v).get_numeral_int();
        result += val;
      }
    } else {
      std::cout << "No solution found.\n";
    }
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

  std::string line;
  std::vector<std::string> schemas;
  size_t index_button = 0;
  std::vector<std::vector<std::vector<uint64_t>>> buttons(line_count);
  std::vector<std::vector<uint64_t>> joltages;
  while (std::cin >> line) {
    size_t pos_open_bracket = line.find('[');
    if (pos_open_bracket != std::string::npos) {
      size_t pos_close_bracket = line.find(']');
      size_t len = pos_close_bracket - pos_open_bracket - 1;
      schemas.push_back(line.substr(pos_open_bracket + 1, len));
    }
    pos_open_bracket = line.find('(');
    if (pos_open_bracket != std::string::npos) {
      size_t pos_close_bracket = line.find(')');
      buttons[index_button].push_back(parse_indices(line.substr(
          pos_open_bracket + 1, pos_close_bracket - pos_open_bracket)));
    }
    pos_open_bracket = line.find('{');
    if (pos_open_bracket != std::string::npos) {
      size_t pos_close_bracket = line.find('}');
      joltages.push_back(parse_indices(line.substr(
          pos_open_bracket + 1, pos_close_bracket - pos_open_bracket)));
      index_button++;
    }
  }

  std::cout << "Part 1: " << solve1(schemas, buttons) << std::endl; // Correct answer: 527
  std::cout << "Part 2: " << solve2(buttons, joltages) << std::endl; // Correct answer: 19810

  return 0;
}
