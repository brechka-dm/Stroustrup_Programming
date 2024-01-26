#include <algorithm>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

using namespace std;

/*
 * This program is a solution of the Exercise 7 from Chapter 8.
 *
 * "Write five names into vector<string> name, then prompt the user to specify
 * the ages of the named people and write them into vector<double> age. Then
 * print the five pairs (name[i],age[i]). Sort the names (sort(name.begin(),
 * name.end())) and print the pairs (name[i], age[i]). ... Then implement the exercise
 * again, allowing an arbitrary number of names. number of names."
 * 
 * It was decided to use int type to store age, instead of the proposed double.
 * 
 */

// Determines which solution variant to use: with fixed or non-fixed number of
// names.
constexpr bool fixed_names = false;

// Sorts an array of ages. The function searches names_template for the next
// name from names and swaps the numbers in the corresponding positions of ages.
// Throws logic_error if name was not found or if the sizes of all vectors are
// not equal.
void sort_ages(vector<int>& ages, const vector<string>& names,
               const vector<string>& names_template) {
  const auto size = names.size();
  if (names_template.size() != size || ages.size() != size)
    throw logic_error("The sizes of vectors passed to sort_ages do not match");

  // Auxiliary temporary vector.
  vector<int> ages_sorted;
  ages_sorted.reserve(size);
  for (int i = 0; i < size; ++i) {
    // See Chapter 21.2.
    const auto names_iter =
        find(names_template.begin(), names_template.end(), names[i]);
    if (names_iter == names_template.end())
      throw logic_error("Name \"" + names[i] +
                        "\" was not found in names_template");
    // Use distance to allocate position in the names_template
    const auto idx = distance(names_template.begin(), names_iter);
    ages_sorted.push_back(ages[idx]);
  }
  // Move without copying.
  // See https://cplusplus.com/reference/utility/move/?kw=move
  ages = std::move(ages_sorted);
}

// Output pairs "(name, adge)".
void print_pairs(const vector<string>& names, const vector<int>& ages) {
  for (int i = 0; i < names.size(); ++i)
    cout << "(" << names[i] << ", " << ages[i] << ")" << endl;
}

// The function implements user input for an exercise variant with a fixed
// number of names. Requests input of age only. Throws logic_error in case of
// incorrect input.
std::pair<vector<string>, vector<int>> fixed_size_input() {
  const vector<string> names{"Jhon", "Michel", "Robert", "Sarah", "Arnold"};
  vector<int> ages;
  ages.reserve(names.size());
  for (int i = 0; i < names.size(); ++i) {
    cout << "Input " << names[i] << " age :";
    int age;
    cin >> age;
    if (!cin) throw logic_error("Invalid input");
    ages.push_back(age);
  }
  return {names, ages};
}

// The function implements user input for an exercise variant with a non-fixed
// number of names. Requests input of name and age. Throws logic_error in case
// of incorrect input.
std::pair<vector<string>, vector<int>> free_size_input() {
  vector<string> names;
  vector<int> ages;
  cout << "Input pairs \"name:age\". Type \"end\" to stop input." << endl;
  string input;
  getline(cin, input);
  if (!cin) throw logic_error("Invalid input");
  while (input != "end") {
    // Use regular expression to get name and adge from input.
    // See Chapter 23.6.
    // This regular expression allows you to search for name and age in the
    // entered string: only capital and small letters are allowed before the
    // colon, only numbers are allowed after the colon. Whitespace characters at
    // the beginning and end of the string, as well as before and after the
    // colon are ignored.
    regex pattern("\\s*([a-zA-Z]+)\\s*:\\s*(\\d+)\\s*");
    smatch matches;
    if (regex_search(input, matches, pattern)) {
      if (matches.size() <= 2) throw logic_error("Invalid input");
      names.push_back(matches[1].str());
      ages.push_back(stoi(matches[2].str()));
    } else
      throw logic_error("Invalid input");
    getline(cin, input);
    if (!cin) throw logic_error("Invalid input");
  }
  return {names, ages};
}

int main() {
  try {
    // Based on the value of fixed_names, we determine which function we are
    // going to use. Functions return a pair of values, copy the corresponding
    // values into variables.
    auto [names, ages] = fixed_names ? fixed_size_input() : free_size_input();
    cout << "Before sort:" << endl;
    print_pairs(names, ages);

    vector<string> names_copy = names;
    sort(names.begin(), names.end());
    sort_ages(ages, names, names_copy);

    cout << "After sort:" << endl;
    print_pairs(names, ages);
  } catch (
      const logic_error& e) {  // catch exceptions in input and sort functions
    cout << e.what() << endl;
    cin.clear();
    return 1;
  }
  return 0;
}