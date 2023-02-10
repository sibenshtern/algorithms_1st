#pragma once

#include <cstddef>
#include <string>

class HashTable {
 public:
  HashTable();
  bool Insert(std::string&& key, int value);
  void InsertOrUpdate(std::string&& key, int value);
  void Remove(const std::string& key);
  int Find(const std::string& key) const;
  size_t Size() const;
};
