#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
 * This program is a solution of the Exercise 14 from Chapter 8.
 * "Write a function that takes an argument of type vector<string> and returns
 * an object of type vector<int> containing the number of characters in each
 * string. In addition, find the shortest and longest strings, as well as the
 * first and last strings according to the lexicographic order".
 */

// Returns vecotr of string lengths.
vector<int> stringsLength(const vector<string>& strings) {
  vector<int> result;
  result.reserve(strings.size());

  // transform applies a functor (lambda expression) to each element of the
  // sequence. In this case, the function
  // [](const string& str) { return str.length(); }
  // is applied to each element of the strings vector to
  // calculate the length of the string.
  // The result is written to result.
  // See https://en.cppreference.com/w/cpp/algorithm/transform.
  transform(strings.begin(), strings.end(), back_inserter(result),
            [](const string& str) { return str.length(); });
  return result;
}

// Displays all elements of the vector on the screen.
template <typename T>
void printVector(const vector<T>& vec) {
  // for_each applies a functor (lambda expression) to each element of the
  // sequence. In this case, the function
  // [](T val) { cout << val << " "; }
  // is applied to each element of the vector, outputting the value
  // of the element to the screen.
  // See https://en.cppreference.com/w/cpp/algorithm/for_each.
  for_each(vec.begin(), vec.end(), [](T val) { cout << val << " "; });
}

int main() {
  vector<string> test{"Hello", "Bjarne", "Stroustrup", "thank", "you",
                      "for",   "a",      "nice",       "C++",   "book"};
  cout << "Strings: " << endl;
  printVector(test);

  const vector<int> lengths{stringsLength(test)};
  cout << endl << "Lengths: " << endl;
  printVector(lengths);

  // max_element and min_element return iterators to the maximum and minimum
  // elements, respectively. To get the value of an element, we use the *
  // operation to dereference the iterators.
  cout << endl
       << "Max length: " << *max_element(lengths.begin(), lengths.end());
  cout << endl
       << "Min length: " << *min_element(lengths.begin(), lengths.end());

  // sort will sort the vector of strings in lexicographic order. We need to
  // take the first and the last word. begin will return the iterator to the
  // first word, rbegin to the last word.
  sort(test.begin(), test.end());
  cout << endl << "First word: " << *test.begin();
  cout << endl << "Last word: " << *test.rbegin();
}