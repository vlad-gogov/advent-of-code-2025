#include <cctype>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <functional>
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

// Answer 131580 6844224

struct Pos {
  int64_t x;
  int64_t y;
  int64_t z;
};

struct Edge {
  uint64_t start;
  uint64_t end;

  int64_t dist2;
};

int64_t dist2(const Pos &a, const Pos &b) {
  int64_t dx = a.x - b.x;
  int64_t dy = a.y - b.y;
  int64_t dz = a.z - b.z;
  return dx * dx + dy * dy + dz * dz;
}

class DSU {
public:
  DSU(size_t n) : p(n, -1) { std::iota(p.begin(), p.end(), 0); }

  int64_t find(int64_t v) {
    if (p[v] == v) {
      return v;
    }
    p[v] = find(p[v]);
    return p[v];
  }

  void mix(int64_t a, int64_t b) { p[find(a)] = find(b); }

private:
  std::vector<int64_t> p;
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

  std::vector<Pos> boxes;
  std::string line;
  while (std::cin >> line) {
    for (char &c : line) {
      if (c == ',') {
        c = ' ';
      }
    }
    std::istringstream iss(line);
    Pos pos;
    iss >> pos.x >> pos.y >> pos.z;
    boxes.push_back(pos);
  }

  std::vector<Edge> edges;
  edges.reserve(boxes.size() * (boxes.size() - 1) / 2);
  for (size_t i = 0; i < boxes.size(); ++i) {
    for (size_t j = i + 1; j < boxes.size(); ++j) {
      edges.push_back({static_cast<uint64_t>(i), static_cast<uint64_t>(j),
                       dist2(boxes[i], boxes[j])});
    }
  }

  std::sort(edges.begin(), edges.end(),
            [](const Edge &A, const Edge &B) { return A.dist2 < B.dist2; });

  DSU dsu(boxes.size());
  size_t result_part1 = 0;
  size_t connections = 0;
  size_t result_part2 = 0;

  for (size_t i = 0; i < edges.size(); ++i) {
    const Edge &edge = edges[i];
    int64_t comp1 = dsu.find(edge.start);
    int64_t comp2 = dsu.find(edge.end);
    if (i == 1000) {
      std::unordered_map<int64_t, int64_t> comp_sizes;
      for (size_t j = 0; j < boxes.size(); ++j) {
        comp_sizes[dsu.find(j)]++;
      }
      std::vector<int64_t> sizes(comp_sizes.size());
      for (const auto &[comp, size] : comp_sizes) {
        sizes.push_back(size);
      }
      std::sort(sizes.begin(), sizes.end(), std::greater<int64_t>());
      if (sizes.size() >= 3) {
        result_part1 = sizes[0] * sizes[1] * sizes[2];
      }
    }

    if (comp1 != comp2) {
      connections++;
      if (connections == boxes.size() - 1) {
        result_part2 = boxes[edge.start].x * boxes[edge.end].x;
      }
      dsu.mix(comp1, comp2);
    }
  }

  std::cout << "Part 1: " << result_part1
            << std::endl; // Correct answer: 131580
  std::cout << "Part 2: " << result_part2
            << std::endl; // Correct answer: 6844224
  return 0;
}
