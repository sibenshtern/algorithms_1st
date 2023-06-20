#pragma once

template <typename T>
class Node {
 public:
  Node(T key_, T value_, Node<T> *parent_ = nullptr)
      : key{key_}, value{value_}, parent{parent_} {};

  bool Insert(T key, T value, Node<T> *parent_node);
  void InsertOrUpdate(T key, T value, Node<T> *parent_node);

  ~Node() {
    delete left;
    delete right;
  }

  T key;
  T value;

  Node<T> *left{nullptr};
  Node<T> *right{nullptr};
  Node<T> *parent{nullptr};
};
