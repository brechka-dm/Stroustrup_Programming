#include "Reverse.h"

std::vector<int> reverse_immut(const std::vector<int>& vector) {
  // Create a new vector for the result.
  std::vector<int> result;
  result.reserve(vector.size());

  // We search the elements of the source vector from end to beginning, write
  // them into the result vector.
  for (auto it = vector.rbegin(); it != vector.rend(); ++it)
    result.push_back(*it);
  return result;
}

void reverse_mut(std::vector<int>& vector) {
  const int n{static_cast<int>(vector.size())};

  // iters is a half of vector size.
  const int iters{static_cast<int>(n / 2)};

  // Swap the first with the last, the second with the penultimate, etc.
  for (int i = 0; i < iters; ++i) std::swap(vector[i], vector[n - i - 1]);
}