#pragma once

#include <pthread.h>

#include <limits>
#include <vector>

template <typename T>
class Stack {
  struct Node {
   public:
    Node(Node *next, Node *back, T value)
        : next_{next}, prev_{back}, value_{value} {};

    Node *AddElement(T value) {
      next_ = new Node(nullptr, this, value);
      return next_;
    }

    void DeleteElement() {
      delete next_;
      next_ = nullptr;
    }

    ~Node() { delete next_; }

    T GetValue() { return value_; }

    Node *BackNode() { return prev_; }

    Node *NextNode() { return next_; }

   private:
    T value_;
    Node *next_ = nullptr;
    Node *prev_ = nullptr;
  };

  Node *start_ = nullptr;
  Node *finish_ = nullptr;
  size_t size_ = 0;

 public:
  void Push(T value);
  T Pop();
  T Top();
  size_t Size() { return size_; };
  bool IsEmpty();

  ~Stack() { delete start_; }
};

template <typename T>
void Stack<T>::Push(T value) {
  if (!start_) {
    auto *tmp_ptr = new Node(nullptr, nullptr, value);
    start_ = tmp_ptr;
    finish_ = tmp_ptr;
  } else {
    finish_ = finish_->AddElement(value);
  }
  ++size_;
}

template <typename T>
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
    Node *tmp_ptr = finish_;
    finish_ = tmp_ptr->BackNode();
    finish_->DeleteElement();
    --size_;
    return temp_value;
  }
}

template <typename T>
T Stack<T>::Top() {
  if (IsEmpty()) return T();

  return finish_->GetValue();
}

template <typename T>
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

template <typename T>
void MinStack<T>::Push(T value) {
  data_.Push(value);
  if (minimums_.IsEmpty() || value < minimums_.Top())
    minimums_.Push(value);
  else
    minimums_.Push(minimums_.Top());
}

template <typename T>
T MinStack<T>::Pop() {
  if (minimums_.Size() > 0) {
    minimums_.Pop();
    return data_.Pop();
  }
  return T();
}

template <typename T>
T MinStack<T>::GetMin() {
  if (minimums_.Size() > 0) return minimums_.Top();
  return T();
}