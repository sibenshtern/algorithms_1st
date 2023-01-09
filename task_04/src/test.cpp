
#include <gtest/gtest.h>

#include <vector>

#include "order_statistics.hpp"

TEST(OrderStatistics, Simple) {
  std::vector<int> data{1, 2, 5, 1, 7, 9, 11, 213, 12, 51, 17, 99};
  ASSERT_EQ(GetOrderStatistics(data, 1), 1);
  ASSERT_EQ(GetOrderStatistics(data, 2), 2);
  ASSERT_EQ(GetOrderStatistics(data, 3), 5);
  ASSERT_EQ(GetOrderStatistics(data, 4), 7);
  ASSERT_EQ(GetOrderStatistics(data, 10), 99);
}