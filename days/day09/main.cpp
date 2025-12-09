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
#include <utility>
#include <vector>

#include "common/util.hpp"

struct Point {
  uint64_t x;
  uint64_t y;
};

struct Line {
  Point start;
  Point end;
};

struct Rectangle {
  Point bottom_left;
  Point top_right;

  size_t area() const {
    return (top_right.x - bottom_left.x + 1) * (top_right.y - bottom_left.y + 1);
  }
};

bool intersects(const Line &l, const Rectangle &rect) {
  return l.end.x > rect.bottom_left.x && l.start.x < rect.top_right.x && l.end.y > rect.bottom_left.y &&
         l.start.y < rect.top_right.y;
}

std::pair<size_t, size_t> solve(const std::vector<Point> &tiles) {
  std::vector<Line> lines;
  for (size_t i = 0; i < tiles.size(); i++) {
    Point current = tiles[i];
    Point next = tiles[(i + 1) % tiles.size()];
    uint64_t x1 = current.x;
    uint64_t y1 = current.y;
    uint64_t x2 = next.x;
    uint64_t y2 = next.y;
    if (x1 > x2) {
      std::swap(x1, x2);
    }
    if (y1 > y2) {
      std::swap(y1, y2);
    }
    lines.push_back({{x1, y1}, {x2, y2}});
  }
  size_t largest_are_all_tiles = 0;
  size_t largest_are_red_and_green = 0;

  for (size_t i = 0; i < tiles.size(); i++) {
    for (size_t j = i + 1; j < tiles.size(); j++) {
      const Point &p1 = tiles[i];
      const Point &p2 = tiles[j];
      uint64_t x1 = std::min(p1.x, p2.x);
      uint64_t y1 = std::min(p1.y, p2.y);
      uint64_t x2 = std::max(p1.x, p2.x);
      uint64_t y2 = std::max(p1.y, p2.y);
      const Rectangle rect{{x1, y1}, {x2, y2}};
      size_t area = rect.area();
      largest_are_all_tiles = std::max(largest_are_all_tiles, area);

      if (area <= largest_are_red_and_green) {
        continue;
      }

      bool includes_only_red_and_green = true;
      for (const auto &line : lines) {
        if (intersects(line, rect)) {
          includes_only_red_and_green = false;
          break;
        }
      }
      if (includes_only_red_and_green) {
        largest_are_red_and_green = area;
      }
    }
  }

  return {largest_are_all_tiles, largest_are_red_and_green};
}

constexpr const char *input_file = "input.txt";

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  [[maybe_unused]] size_t line_count = count_lines(input_file);

  std::ifstream file(input_file);
  // Redirect standard input to read from the file
  if (file) {
    std::cin.rdbuf(file.rdbuf());
  }

  std::vector<Point> tiles;
  std::string line;
  while (std::cin >> line) {
    std::pair<uint64_t, uint64_t> coords = parse_range(line, ',');
    tiles.push_back({coords.first, coords.second});
  }

  const auto &[result_part1, result_part2] = solve(tiles);

  std::cout << "Part 1: " << result_part1
            << std::endl; // Correct answer: 4750092396
  std::cout << "Part 2: " << result_part2
            << std::endl; // Correct answer: 1468516555
  return 0;
}
