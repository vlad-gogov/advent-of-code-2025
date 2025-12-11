#pragma once

#include <cstdint>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

template <typename T> T from_string(const std::string &s);

template <> inline int64_t from_string<int64_t>(const std::string &s) {
  return std::stoll(s);
}
template <> inline uint64_t from_string<uint64_t>(const std::string &s) {
  return std::stoull(s);
}

template <typename T>
std::pair<T, T> parse_numbers(const std::string &line, const char delimiter) {
  auto pos = line.find(delimiter);
  return {from_string<T>(line.substr(0, pos)),
          from_string<T>(line.substr(pos + 1))};
}

std::uint64_t count_lines(const std::string &filename);

template <typename T> void printVector(const std::vector<T> &vec) {
  for (const auto &item : vec) {
    std::cout << item << " ";
  }
  std::cout << std::endl;
}
