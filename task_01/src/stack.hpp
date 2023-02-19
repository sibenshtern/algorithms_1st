#pragma once

#include <pthread.h>
#include <vector>
#include <limits>

template <typename T>
class Node {
 public:
  Node(Node<T> *next, Node<T> *back, T value) : next_{next}, back_{back}, value_{value} {};

  Node<T> *AddElement(T value) {
      next_ = new Node<T>(nullptr, this, value);
      return next_;
  }

  void DeleteElement() {
      delete next_;
      next_ = nullptr;
  }

  ~Node() {
      delete next_;
  }

  T GetValue() {
      return value_;
  }

  Node<T> *BackNode() {
      return back_;
  }

  Node<T> *NextNode() {
      return next_;
  }

 private:
  T value_;
  Node *next_ = nullptr;
  Node *back_ = nullptr;
};

template <typename T>
class Stack {
 public:
  void Push(T value);
  T Pop();
  T Top();
  size_t Size() { return size_; };
  bool IsEmpty();

  ~Stack() {
    delete start_;
  }

 private:
  Node<T> *start_ = nullptr;
  Node<T> *finish_ = nullptr;
  size_t size_ = 0;
};

template<typename T>
void Stack<T>::Push(T value) {
  if (!start_) {
    auto *tmp_ptr = new Node<T>(nullptr, nullptr, value);
    start_ = tmp_ptr;
    finish_ = tmp_ptr;
  } else if (start_ == finish_) {
    finish_ = start_->AddElement(value);
  } else {
    finish_ = finish_->AddElement(value);
  }
  ++size_;
}

template<typename T>
T Stack<T>::Pop() {
  if (IsEmpty()) {
    return T();
  } else if (start_ == finish_) {
    T temp_value = finish_->GetValue();
    delete start_;
    start_ = nullptr;
    finish_ = nullptr;
    --size_;
    return temp_value;
  } else {
    T temp_value = finish_->GetValue();
    Node<T> *tmp_ptr = finish_;
    finish_ = tmp_ptr->BackNode();
    finish_->DeleteElement();
    --size_;
    return temp_value;
  }
}

template<typename T>
T Stack<T>::Top() {
  if (IsEmpty())
    return T();

  return finish_->GetValue();
}

template<typename T>
bool Stack<T>::IsEmpty() {
  return !start_;
}

template <typename T>
class MinStack {
 public:
  void Push(T value);
  T Pop();
  T GetMin();

 private:
  Stack<T> data_;
  Stack<T> minimums_;
};

template<typename T>
void MinStack<T>::Push(T value) {
  data_.Push(value);
  if (minimums_.IsEmpty() || value < minimums_.Top())
    minimums_.Push(value);
  else
    minimums_.Push(minimums_.Top());
}

template<typename T>
T MinStack<T>::Pop() {
  if (minimums_.Size() > 0) {
    minimums_.Pop();
    return data_.Pop();
  }
  return T();
}

template<typename T>
T MinStack<T>::GetMin() {
  if (minimums_.Size() > 0)
    return minimums_.Top();
  return T();
}