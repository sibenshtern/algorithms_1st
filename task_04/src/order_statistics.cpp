#include "order_statistics.hpp"

#include <algorithm>

int GetOrderStatistics(const std::vector<int>& data, size_t n) {
  std::vector<int> tmp(data);

  std::sort(tmp.begin(), tmp.end());

  return tmp[n];
}
