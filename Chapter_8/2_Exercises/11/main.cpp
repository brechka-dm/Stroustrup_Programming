#include <iostream>
#include <vector>

using namespace std;

/*
 * This program is a solution of the Exercise 11 from the Chapter 8.
 * "Write a maxv() function that returns the largest element of a vector".
 */

// Usint template to make function more universal: we can use vectors of any
// type for which the operation > is defined. See Chapter 19.3.
template <typename T>
T maxv(const vector<T>& vec) {
  // At the beginning we assume that the first element of the vector is maximal.
  // This may or may not be true.
  T m = vec[0];
  // Check all other elements (from the second to the last).
  for (int i = 1; i < vec.size(); ++i)
    // If an element larger than the maximal is found - update the maximum.
    if (vec[i] > m) m = vec[i];
  return m;
}

int main() {
  const vector<int> test{10, 30, 11, -8, 123, -45, 99, -13, 70, 6};
  cout << "Vector: ";
  for (int i = 0; i < test.size(); ++i) cout << test[i] << " ";
  cout << endl << "Max: " << maxv(test);
}