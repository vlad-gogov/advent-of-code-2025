#include "util.hpp"

#include <fstream>

std::uint64_t count_lines(const std::string &filename) {
    std::ifstream f(filename);
    std::uint64_t count = 0;
    std::string line;
    while (std::getline(f, line)) {
        count++;
    }
    return count;
}

std::pair<std::uint64_t, std::uint64_t> parse_range(const std::string &line,
                                                    const char delimiter) {
  size_t dash_pos = line.find(delimiter);
  if (dash_pos == std::string::npos) {
    throw std::invalid_argument("Invalid range format: " + line);
  }
  std::uint64_t first = std::stoull(line.substr(0, dash_pos));
  std::uint64_t second = std::stoull(line.substr(dash_pos + 1));
  return {first, second};
}
