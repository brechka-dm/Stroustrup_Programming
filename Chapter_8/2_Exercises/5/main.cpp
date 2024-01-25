#include <iostream>

#include "Print.h"
#include "Reverse.h"

/*
 * This program is a solution for the Exercise 5 from Chapter 8.
 *
 * "Write two functions that change the order of elements in an object of
 * vector<int> type. The first function, which reverses the order of elements,
 * must create a new object of vector class, while the original object of vector
 * class must remain unchanged. The other function must change the order of
 * elements without without using other vectors."
 *
 * Reverse functions implemented in the separate file.
 */

int main() {
  std::vector<int> test{1, 3, 5, 7, 9};
  // reverse_immut creates a new vector with a changed order of elements. The
  // original vector is not changed.
  print("Immutable", reverse_immut(test));

  // First change the order of elements in the test vector, then output this
  // vector.
  reverse_mut(test), print("Mutable", test);
  return 0;
}