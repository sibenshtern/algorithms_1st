#include "stack.hpp"
#include <climits>

void Stack::Push(int value) { data_.push_back(value); }

int Stack::Pop() {
  if (data_.size() == 0) { return INT_MAX; }

  auto result = data_.back();
  data_.pop_back();
  return result;
}

int Stack::Top() {
  if (data_.size() == 0) { return INT_MAX; }
  
  return data_.back();
}

int Stack::Size() { return data_.size(); }

void MinStack::Push(int value) {
  data_.push_back(value);
  if (minimums_.Size() == 0 || value < minimums_.Top())
    minimums_.Push(value);
  else
    minimums_.Push(minimums_.Top());
}

int MinStack::Pop() {
  if (data_.size() == 0) { return INT_MAX; }

  auto result = data_.back();
  minimums_.Pop();
  data_.pop_back();
  return result;
}

int MinStack::GetMin() {
  return minimums_.Top();
}