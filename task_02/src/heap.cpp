#include "heap.hpp"

#include <cstddef>
#include <stdexcept>

void MinHeap::Push(int n) { data_.push(n); }

int MinHeap::Pop() {
  if (data_.empty()) throw std::out_of_range("Empty heap");
  auto result = data_.top();
  data_.pop();
  return result;
}

size_t MinHeap::Size() { return data_.size(); }
