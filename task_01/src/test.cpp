#include <gtest/gtest.h>

#include <climits>
#include <stack>

#include "stack.hpp"

TEST(StackTestInt, Simple) {
  Stack<int> stack;
  stack.Push(1);              // Stack [1]
  ASSERT_EQ(stack.Pop(), 1);  // Stack []
  stack.Push(1);              // Stack [1]
  stack.Push(2);              // Stack [1, 2]
  ASSERT_EQ(stack.Pop(), 2);  // Stack [1]
  ASSERT_EQ(stack.Pop(), 1);  // Stack []
  stack.Push(1);              // Stack [1]
  stack.Push(2);              // Stack [1, 2]
  ASSERT_EQ(stack.Pop(), 2);  // Stack [1]
  stack.Push(3);              // Stack [1, 3]
  ASSERT_EQ(stack.Pop(), 3);  // Stack [1]
  ASSERT_EQ(stack.Pop(), 1);  // Stack []
  ASSERT_EQ(stack.Pop(), 0);
}

TEST(StackTestFloat, Simple) {
  Stack<float> stack;
  stack.Push(1.0f);              // Stack [1]
  ASSERT_EQ(stack.Pop(), 1.0f);  // Stack []
  stack.Push(1.5f);              // Stack [1]
  stack.Push(2.8f);              // Stack [1, 2]
  ASSERT_EQ(stack.Pop(), 2.8f);  // Stack [1]
  ASSERT_EQ(stack.Pop(), 1.5f);  // Stack []
  stack.Push(1.f);               // Stack [1]
  stack.Push(2.f);               // Stack [1, 2]
  ASSERT_EQ(stack.Pop(), 2.f);   // Stack [1]
  stack.Push(3.f);               // Stack [1, 3]
  ASSERT_EQ(stack.Pop(), 3.f);   // Stack [1]
  ASSERT_EQ(stack.Pop(), 1.f);   // Stack []
  ASSERT_EQ(stack.Pop(), 0.f);
}

TEST(MinStackTest, Simple) {
  MinStack<int> stack;
  stack.Push(1);  // Stack [1]
  ASSERT_EQ(stack.GetMin(), 1);
  ASSERT_EQ(stack.Pop(), 1);  // Stack []
  stack.Push(1);              // Stack [1]
  stack.Push(2);              // Stack [1, 2]
  ASSERT_EQ(stack.GetMin(), 1);
  ASSERT_EQ(stack.Pop(), 2);  // Stack [1]
  ASSERT_EQ(stack.Pop(), 1);  // Stack []
  stack.Push(1);              // Stack [1]
  stack.Push(2);              // Stack [1, 2]
  ASSERT_EQ(stack.GetMin(), 1);
  ASSERT_EQ(stack.Pop(), 2);  // Stack [1]
  stack.Push(3);              // Stack [1, 3]
  ASSERT_EQ(stack.GetMin(), 1);
  ASSERT_EQ(stack.Pop(), 3);  // Stack [1]
  ASSERT_EQ(stack.Pop(), 1);  // Stack []
  ASSERT_EQ(stack.Pop(), 0);  // Stack []
}