
#include <gtest/gtest.h>

#include <vector>

#include "hashtable.hpp"

TEST(HashTable, Simple) {
  HashTable data;
  data.Insert("aaaa", 1);
  ASSERT_EQ(data.Find("aaaa"), 1);
  data.InsertOrUpdate("aaaa", 2);
  ASSERT_EQ(data.Find("aaaa"), 2);
}