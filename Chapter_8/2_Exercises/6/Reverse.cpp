#include "Reverse.h"

std::vector<std::string> reverse_immut(const std::vector<std::string>& vector) {
  std::vector<std::string> result;
  for (auto it = vector.rbegin(); it != vector.rend(); ++it)
    result.push_back(*it);
  return result;
}

void reverse_mut(std::vector<std::string>& vector) {
  const int n{static_cast<int>(vector.size())};
  const int iters{static_cast<int>(n / 2)};
  for (int i = 0; i < iters; ++i) std::swap(vector[i], vector[n - i - 1]);
}