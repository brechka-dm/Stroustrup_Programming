#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void sort_ages(vector<int>& ages, const vector<string>& names,
               const vector<string>& names_template) {
  // throw if error
  // check vector sizes
  vector<int> ages_sorted;
  ages_sorted.reserve(ages.size());
  for (int i = 0; i < names.size(); ++i) {
    const auto names_iter =
        find(names_template.begin(), names_template.end(), names[i]);
    if (names_iter == names_template.end()) {
      // error
    }
    const auto idx = distance(names_template.begin(), names_iter);
    ages_sorted.push_back(ages[idx]);
  }
  ages = std::move(ages_sorted);
}

void print_pairs(const vector<string>& names, const vector<int>& ages) {
  for (int i = 0; i < names.size(); ++i)
    cout << "(" << names[i] << ", " << ages[i] << ")" << endl;
}

int main() {
  vector<string> names{"Jhon", "Michel", "Robert", "Sarah", "Arnold"};
  vector<int> ages;
  ages.reserve(names.size());
  for (int i = 0; i < names.size(); ++i) {
    cout << "Input " << names[i] << " age :";
    int age;
    cin >> age;
    //throw if error
    ages.push_back(age);
  }
  cout << "Before sort:" << endl;
  print_pairs(names, ages);

  vector<string> names_copy = names;
  sort(names.begin(), names.end());
  sort_ages(ages, names, names_copy);

  cout << "After sort:" << endl;
  print_pairs(names, ages);
}