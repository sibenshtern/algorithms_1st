#pragma once

#include <stdexcept>
#include <vector>

template <typename T>
class MinHeap {
 public:
  void Push(T value);
  void ShiftUp(size_t index);
  void ShiftDown(size_t index);

  T Pop();
  size_t Size();

 private:
  std::vector<T> data_;
};

template <typename T>
void MinHeap<T>::Push(T value) {
  data_.push_back(value);
  ShiftUp(data_.size() - 1);
}

template <typename T>
T MinHeap<T>::Pop() {
  if (data_.empty()) throw std::out_of_range("Empty heap");

  T temp_value = data_[0];
  data_[0] = data_.back();
  data_.pop_back();
  ShiftDown(0);
  return temp_value;
}

template <typename T>
size_t MinHeap<T>::Size() {
  return data_.size();
}

template <typename T>
void MinHeap<T>::ShiftUp(size_t index) {
  size_t parent = index / 2;
  if (index > 0 && data_[index] < data_[parent]) {
    std::swap(data_[index], data_[parent]);
    ShiftUp(parent);
  } else
    return;
}

template <typename T>
void MinHeap<T>::ShiftDown(size_t index) {
  size_t left = 2 * index + 1;
  size_t right = 2 * index + 2;

  if (left > data_.size() - 1 || index > data_.size())
    return;
  else {
    if (data_[index] == data_[left] && data_[left] == data_[right])
      return;
    else if (data_[index] > data_[left] && data_[left] <= data_[right]) {
      std::swap(data_[left], data_[index]);
      ShiftDown(left);
    } else if (data_[index] > data_[right] && data_[left] > data_[right]) {
      std::swap(data_[right], data_[index]);
      ShiftDown(right);
    }
  }
}

template <typename T>
std::vector<T> Sort(const std::vector<T> &data) {
  MinHeap<T> heap;
  for (int i = 0; i < data.size(); ++i) heap.Push(data[i]);

  std::vector<T> result(data.size());
  for (int i = 0; i < data.size(); ++i) result[i] = heap.Pop();
  return result;
}