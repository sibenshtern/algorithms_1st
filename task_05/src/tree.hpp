#pragma once

#include <node.hpp>

template <typename T>
class Tree {
 public:
  Tree();
  bool Insert(T key, T value);
  void InsertOrUpdate(T key, T value);
  T Find(T key) const;

  ~Tree() { delete root_; }

 private:
  T Find(T key, Node<T> *node) const;
  Node<T> *root_{nullptr};
};

template <typename T>
Tree<T>::Tree(){};

template <typename T>
bool Tree<T>::Insert(T key, T value) {
  Node<T> *tmp = new Node<T>(key, value);

  Node<T> *parent_node = nullptr;
  Node<T> *current_node = root_;

  while (current_node) {
    parent_node = current_node;
    if (tmp->key < current_node->key)
      current_node = current_node->left;
    else if (tmp->key > current_node->key)
      current_node = current_node->right;
    else {
      delete tmp;
      return false;
    }
  }
  tmp->parent = parent_node;
  if (!parent_node) {
    root_ = tmp;
  } else if (tmp->key < parent_node->key) {
    parent_node->left = tmp;
  } else if (tmp->key > parent_node->key) {
    parent_node->right = tmp;
  } else {
    delete tmp;
    return false;
  }
  return true;
}

template <typename T>
void Tree<T>::InsertOrUpdate(T key, T value) {
  Node<T> *tmp = new Node<T>(key, value);

  Node<T> *parent_node = nullptr;
  Node<T> *current_node = root_;

  while (current_node) {
    parent_node = current_node;
    if (tmp->key < current_node->key)
      current_node = current_node->left;
    else if (tmp->key > current_node->key)
      current_node = current_node->right;
    else {
      current_node = tmp;
      return;
    }
  }
  tmp->parent = parent_node;
  if (!parent_node) {
    root_ = tmp;
  } else if (tmp->key < parent_node->key) {
    parent_node->left = tmp;
  } else if (tmp->key > parent_node->key) {
    parent_node->right = tmp;
  } else {
    tmp->parent = parent_node->parent;
    parent_node = tmp;
  }
}

template <typename T>
T Tree<T>::Find(T key) const {
  return Find(key, root_);
}

template <typename T>
T Tree<T>::Find(T key, Node<T> *node) const {
  if (!node || node->key == key) {
    return node;
  }

  if (key < node->key) return Find(key, node->left);
  return Find(key, node->right);
}