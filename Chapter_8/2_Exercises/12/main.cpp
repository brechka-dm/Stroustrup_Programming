#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/*
 * This program is a solution of the Exercise 12 from Chapter 8.
 * "Write a function that finds the smallest and the largest elements of a
 * vector of a vector that is its argument, and also calculates their average
 * and median."
 */

// This struct uses as a return value of the desired function.
// Using template to make function more universal (see Chapter 19.3).
// We can use any numeric vector type (we cannot use string as it is imposible
// to calculate average for strings).
template <typename T>
struct VectorParameters {
  const T max;
  const T min;
  const double avg;     // average is always double.
  const double median;  // median is always double.
};

// This function calculates vector parameters.
// Vector must have at least 2 elements.
template <typename T>
VectorParameters<T> calcVectorParameters(const vector<T>& vec) {
  // Calculate max and min as it was described in Ex. 11.
  T mx{vec[0]};
  T mn{vec[0]};
  for (int i = 1; i < vec.size(); ++i) {
    if (vec[i] > mx) mx = vec[i];
    if (vec[i] < mn) mn = vec[i];
  }

  // We calculate the median as it is written in the
  // https://en.wikipedia.org/wiki/Median, for even and odd number of elements
  // in the vector, the calculation formulas are different.
  // To calculate the median, we first need to sort the vector, but the original
  // vector is passed by constant reference, so we make a copy of it.
  vector<T> vecCopy = vec;
  sort(vecCopy.begin(), vecCopy.end());
  const int middle{static_cast<int>(vecCopy.size() * 0.5)};
  const double median{vecCopy.size() % 2 != 0
                          ? vecCopy[middle]
                          : (vecCopy[middle] + vecCopy[middle - 1]) * 0.5};

  // Calc averege as (max+min)/2.
  return {mx, mn, (mx + mn) * 0.5, median};
}

int main() {
  vector<int> test{10, 30, 11, -8, 123, -45, 99, -13, 70, 6};
  cout << "Vector: ";
  const VectorParameters params{calcVectorParameters(test)};
  for (int i = 0; i < test.size(); ++i) cout << test[i] << " ";
  cout << endl
       << "Max: " << params.max << endl
       << "Min: " << params.min << endl
       << "Averege: " << params.avg << endl
       << "Median: " << params.median;
}