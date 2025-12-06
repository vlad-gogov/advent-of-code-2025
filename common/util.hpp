#pragma once

#include <cstdint>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

std::uint64_t count_lines(const std::string& filename);
std::pair<std::uint64_t, std::uint64_t> parse_range(const std::string &line);

template <typename T> void printVector(const std::vector<T> &vec) {
  for (const auto &item : vec) {
    std::cout << item << " ";
  }
  std::cout << std::endl;
}
