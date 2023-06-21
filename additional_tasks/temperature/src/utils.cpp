#include "utils.hpp"

#include <algorithm>

std::vector<int> CalculateDaysBeforWarmup(
    const std::vector<float>& temperature) {
  Stack<std::pair<float, int>> temp;
  std::vector<int> answer(temperature.size());

  for (int i = 0; i < temperature.size(); ++i) {
    while (temp.Top().first < temperature[i] && !temp.IsEmpty()) {
      answer[temp.Top().second] = i - temp.Top().second;
      temp.Pop();
    }
    temp.Push({temperature[i], i});
  }

  while (!temp.IsEmpty()) temp.Pop();

  return answer;
}
