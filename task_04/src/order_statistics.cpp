#include "order_statistics.hpp"

#include <algorithm>
#include <random>

int randint(int a, int b) {
  std::random_device r;
  std::mt19937_64 engine(r());
  std::uniform_int_distribution<int> uniform_dist(a, b);
  return uniform_dist(engine);
}

int GetOrderStatistics(const std::vector<int> &data, size_t k) {
  if (data.size() == 1) return data[0];

  std::vector<int> less;
  less.reserve(data.size());
  std::vector<int> equal;
  equal.reserve(data.size());
  std::vector<int> more;
  more.reserve(data.size());

  int x = data[randint(0, data.size())];

  for (int i = 0; i < data.size(); ++i) {
    if (data[i] < x)
      less.push_back(data[i]);
    else if (data[i] == x)
      equal.push_back(data[i]);
    else
      more.push_back(data[i]);
  }

  if (k < less.size())
    return GetOrderStatistics(less, k);
  else if (k < less.size() + equal.size())
    return x;
  else
    return GetOrderStatistics(more, k - less.size() - equal.size());
}
