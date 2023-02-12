#pragma once

#include <vector>
#include <limits>

class Stack {
 public:
  void Push(int value);
  int Pop();
  int Top();
  int Size();

 private:
  std::vector<int> data_;
};

class MinStack {
 public:
  void Push(int value);
  int Pop();
  int GetMin();

 private:
  std::vector<int> data_;
  Stack minimums_;
};