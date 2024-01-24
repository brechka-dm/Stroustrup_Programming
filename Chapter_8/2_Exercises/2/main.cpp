#include <vector>

#include "Print.h"

/*
 * This program is a solution of Excercise 2 from Chapter 8.
 *
 * "Write a print() function that prints a vector of integers to the cout stream.
 * integers. Let it have two arguments: a string for commenting the result and
 * an object of class vector".
 *
 * The function is implemented in separate file.
 */

int main() {
  const std::vector<int> test{-1, 0, 2, 3, 98, -108};
  print("test vector", test);
}