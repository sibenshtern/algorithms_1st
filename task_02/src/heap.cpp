#include "heap.hpp"

#include <algorithm>
#include <stdexcept>

void MinHeap::Push(int n) {
  data_.push_back(n);
  int i = Size() - 1;
  int parent = (i - 1) / 2;

  while (i > 0 && data_[parent] > data_[i]) {
    std::swap(data_[parent], data_[i]);
    i = parent;
    parent = (i - 1) / 2;
  }
}

void MinHeap::Heapify() {
  int i = 0;
  int child = 2 * i + 1;
  if (child >= Size())
    return;

  if (data_[2 * i + 1] > data_[2 * i + 2])
    child = 2 * i + 1;
  
  while (child < Size() && data_[child] > data_[i])
    std::swap(data_[child], data_[i]);

    i = child;
  if (child >= Size())
    return;

  if (data_[2 * i + 1] > data_[2 * i + 2])
    child = 2 * i + 1;
} 

int MinHeap::Pop() {
  if (data_.empty()) throw std::out_of_range("Empty heap");
  auto result = data_.back();
  data_.pop_back();
  return result;
}

size_t MinHeap::Size() { return data_.size(); }
