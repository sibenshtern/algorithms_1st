#pragma once

#include <cstddef>
#include <functional>
#include <queue>
#include <vector>

class MinHeap {
 public:
  void Push(int value);
  int Pop();
  size_t Size();

 private:
  std::priority_queue<int, std::vector<int>, std::greater<int>> data_;
};
