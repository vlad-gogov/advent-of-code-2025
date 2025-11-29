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
