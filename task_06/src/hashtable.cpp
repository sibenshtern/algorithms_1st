#include "hashtable.hpp"

#include <string>

HashTable::HashTable() {}

bool HashTable::Insert(std::string&& key, int value) { return true; }

void HashTable::InsertOrUpdate(std::string&& key, int value) {}

void HashTable::Remove(const std::string& key) {}

int HashTable::Find(const std::string& key) const { return 0; }
