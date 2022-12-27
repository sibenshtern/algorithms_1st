#include "sort.hpp"

#include <algorithm>
#include <vector>

std::vector<int> Sort(const std::vector<int>& data) {
  std::vector<int> result = data;
  std::sort(result.begin(), result.end());
  return result;
}