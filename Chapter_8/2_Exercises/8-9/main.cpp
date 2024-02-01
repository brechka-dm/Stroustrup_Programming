#include <cstdlib>
#include <ctime>
#include <iostream>

#include "rand.h"

using namespace std;

/*
 * This program is a solution of the Exercise 8 and 9 from the Chapter 8.
 * 8. "Write a simple randint() function that generates pseudo-random numbers in
 * the range [0:MAXINT]."
 * 9. "Write a function that computes a pseudorandom integer in the range [a:b):
 * rand_in_range(int a, int b) using the randint() function from the previous
 * exercise."
 *
 * The solution uses the formula for the linear congruent generator described in
 * https://habr.com/ru/articles/499490/.
 *
 * Implementation of functions for number generation is placed in a separate
 * file.
 *
 * The maxrand() function returns the maximum random number that can be
 * generated (analog of MAXINT from the task).
 *
 * The main() function uses the rand() function from the <cstdlib> standard
 * library to compare results.
 */

int main() {
  // Using value of the time as a random seed.
  const long long seed{time(0)};
  srand(seed);
  ex8::set_seed(seed);

  constexpr int a{1};
  constexpr int b{10};
  constexpr int n{20};

  for (int i = 0; i < n; ++i) cout << ex8::rand_in_range(a, b) << " ";
  cout << endl;
  for (int i = 0; i < n; ++i) cout << a + rand() % (b - a) << " ";

  return 0;
}