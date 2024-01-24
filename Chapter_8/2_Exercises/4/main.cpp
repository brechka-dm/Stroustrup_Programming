#include <iostream>

#include "Fibonacci.h"

using namespace std;

/*
 * This program is a solution for Exercise 4 of Chapter 8.
 *
 * "A variable of int type can store integers not exceeding a certain maximum
 * number. Calculate the approximation of this maximum number using the
 * fibonacci() function".
 *
 * To solve the problem we use the assumption that when a variable of int type
 * overflows the value of the variable becomes negative, so we need to find the
 * last Fibonacci number that does not overflow the variable (the last positive
 * number).
 */

// Returns iterator to first negative number from the beginning of the vector.
// See Chapter 20.3 for iterators explanations.
std::vector<int>::const_iterator findFirstNegative(
    const std::vector<int>& vector) {
  for (auto it = vector.begin(); it != vector.end(); ++it)
    if (*it < 0) return it;
  return vector.end();
}

int main() {
  std::vector<int> f_nums;
  const int n{20};
  f_nums.reserve(n);
  // Calculate first 20 Fibonacci.
  fibonacci(0, 1, f_nums, n);
  auto iter = findFirstNegative(f_nums);
  // Continue calculate next 20 Fibonacci until first negative found.
  while (iter == f_nums.end()) {
    // rbegin is a first elemen of the reverse iterator i.e. the last element of
    // the vector. Thus rbegin++ is the penultimate element of the vector.
    const int x{*(++f_nums.rbegin())};
    const int y{*f_nums.rbegin()};
    f_nums.clear();
    f_nums.reserve(n);
    fibonacci(x, y, f_nums, n);
    iter = findFirstNegative(f_nums);
  }
  // iter points to a negative number, but we need the previous (positive)
  // number, so we use --.
  cout << "Calculated: \t" << *(--iter) << endl;
  // For comparison we output the real maximum value of int.
  // See Chapter 24.2.1 for numeric_limits explanation.
  cout << "Real: \t\t" << std::numeric_limits<int>::max();
}