#pragma once

class Tree {
 public:
  Tree();
  bool Insert(int key, int value);
  void InsertOrUpdate(int key, int value);
  int Find(int key) const;
};
