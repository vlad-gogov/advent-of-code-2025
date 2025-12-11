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

using Graph = std::unordered_map<std::string, std::vector<std::string>>;

struct Solver {
  Graph graph;
  std::unordered_map<std::string, size_t> req_index;
  using CacheKey = std::pair<std::string, size_t>;
  std::map<CacheKey, size_t> caches;

  Solver(const Graph &graph, const std::vector<std::string> required = {})
      : graph(graph) {
    if (!required.empty()) {
      for (size_t i = 0; i < required.size(); i++) {
        req_index[required[i]] = i;
      }
    }
  }

  size_t dfs(const std::string &current_node, const std::string &finish_node,
             size_t current_mask) {
    if (const auto &it = req_index.find(current_node); it != req_index.end()) {
      current_mask |= (1 << it->second);
    }
    if (current_node == finish_node) {
      size_t full_mask = ((1ULL << req_index.size()) - 1);
      return current_mask == full_mask;
    }
    CacheKey key(current_node, current_mask);
    if (const auto &it = caches.find(key); it != caches.end()) {
      return it->second;
    }

    size_t result = 0;
    if (const auto &it = graph.find(current_node); it != graph.end()) {
      for (const auto &next : it->second) {
        result += dfs(next, finish_node, current_mask);
      }
    }
    caches[key] = result;
    return result;
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

  std::vector<std::string> names;
  std::vector<std::vector<std::string>> devices(line_count);
  int index_devices = -1;

  std::string line;
  while (std::cin >> line) {
    size_t pos = line.find(':');
    if (pos != std::string::npos) {
      names.push_back(line.substr(0, pos));
      index_devices++;
    } else {
      devices[index_devices].push_back(line);
    }
  }

  Graph graph;
  for (size_t i = 0; i < names.size(); i++) {
    for (size_t j = 0; j < devices[i].size(); j++) {
      graph[names[i]].push_back(devices[i][j]);
    }
  }
  std::cout << "Part 1: " << Solver(graph).dfs("you", "out", 0)
            << std::endl; // Correct answer 796
  std::cout << "Part 2: " << Solver(graph, {"dac", "fft"}).dfs("svr", "out", 0)
            << std::endl; // Correct answer 294053029111296
  return 0;
}
