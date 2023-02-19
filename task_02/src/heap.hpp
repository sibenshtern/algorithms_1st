#pragma once

#include <vector>

class MinHeap {
 public:
  void Push(int value);
  void Heapify();
  int Pop();
  size_t Size();

 private:
  std::vector<int> data_;
};
