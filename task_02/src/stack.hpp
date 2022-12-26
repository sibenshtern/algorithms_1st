#pragma once

class Stack {
 public:
  void Push(int value);
  int Pop();
};

class MinStack {
 public:
  void Push(int value);
  int Pop();
  int GetMin();
};