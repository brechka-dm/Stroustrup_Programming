#include <vector>

#include "Fibonacci.h"
#include "Print.h"

/*
 * This program is solution of Exercise 3 from Chapter 8.
 *
 * "Create a vector of Fibonacci numbers and print them using the function from
 * Exercise 2. To create a vector, write the function fibonacci(x, y, v, n),
 * where the arguments x and y are of type int, the argument v is an empty
 * variable of type vector<int>, and the argument n is the number of elements to
 * be written into vector v."
 */

int main() {
  const int n{10};
  std::vector<int> result;
  result.reserve(n);
  fibonacci(1, 2, result, n);
  print("Fibonacci", result);
}