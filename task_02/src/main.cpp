#include <iostream>

#include "heap.hpp"

int main() {
  MinHeap<int> heap;
  heap.Push(6);  // [6]
  heap.Push(1);  // [1, 6]
  heap.Push(2);  // [1, 2, 6]
  heap.Push(3);  // [1, 2, 3, 6]
  heap.Push(5);  // [1, 2, 3, 5, 6]
  heap.Push(4);  // [1, 2, 3, 4, 5, 6]
  for (int i = 0; i < 6; ++i) std::cout << heap.Pop() << "\n";
  return 0;
}
