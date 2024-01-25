#include <iostream>

#include "Reverse.h"

using namespace std;

/*
 * This program is a solution for the Exercise 6 from Chapter 8.
 *
 * "Write variants of the functions from exercise 5 for the vector<string> class."
 *
 * The solution is completely similar to exercise 5.
 */

// This function prints string vector.
void print_vector(const string& message, const vector<string>& vec) {
  cout << message << ": ";
  for (auto it = vec.begin(); it != vec.end(); ++it) cout << *it << " ";
  cout << endl;
}

int main() {
  vector<string> test{"Hello", "Bjarne", "Stroustrup"};
  print_vector("Immutable", reverse_immut(test));
  reverse_mut(test), print_vector("Mutable", test);
}