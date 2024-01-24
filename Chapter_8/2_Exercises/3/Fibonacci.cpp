#include "Fibonacci.h"

void fibonacci(int x, int y, std::vector<int>& v, int n) {
  v.push_back(x);
  v.push_back(y);
  // Start from 2 as first 2 numbers already placed in vector.
  for (int i = 2; i < n; ++i) {
    const int next{x + y};
    v.push_back(next);
    x = y, y = next;
  }
}