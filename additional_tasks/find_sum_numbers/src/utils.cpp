#include "utils.hpp"

#include <algorithm>

std::pair<int, int> GetNumbersOfSum(const std::vector<int>& numbers, int sum) {
  int first_pointer{0};
  int second_pointer{static_cast<int>(numbers.size()) - 1};

  int pointers_sum = numbers[first_pointer] + numbers[second_pointer];
  while (pointers_sum != sum || first_pointer != second_pointer) {
    if (pointers_sum < sum)
      ++first_pointer;
    else if (pointers_sum > sum)
      second_pointer--;
    else if (pointers_sum == sum)
      break;
    pointers_sum = numbers[first_pointer] + numbers[second_pointer];
  }

  if (pointers_sum == sum && first_pointer != second_pointer)
    return {first_pointer, second_pointer};
  return {0, 0};
}