#pragma once

#include <cstdint>
#include <string>
#include <utility>

std::uint64_t count_lines(const std::string& filename);
std::pair<std::uint64_t, std::uint64_t> parse_range(const std::string &line);
