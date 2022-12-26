
#include <gtest/gtest.h>

#include "sort.hpp"

TEST(SortTest, Simple) {
  ASSERT_EQ(Sort({}), std::vector<int>{});
  ASSERT_EQ(Sort({1}), std::vector<int>{1});
  ASSERT_EQ(Sort({1, 2, 3}), std::vector<int>{1, 2, 3});
  ASSERT_EQ(Sort({3, 2, 1}), std::vector<int>{1, 2, 3});
}