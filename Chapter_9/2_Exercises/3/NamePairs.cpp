#include "NamePairs.h"

#include <algorithm>
#include <iostream>

using namespace std;

namespace {
void sort_ages(vector<double>& ages, const vector<string>& names,
               const vector<string>& names_template) {
  const auto size = names.size();
  if (names_template.size() != size || ages.size() != size)
    throw logic_error("The sizes of vectors passed to sort_ages do not match");

  vector<double> ages_sorted;
  ages_sorted.reserve(size);
  for (int i = 0; i < size; ++i) {
    const auto names_iter =
        find(names_template.begin(), names_template.end(), names[i]);
    if (names_iter == names_template.end())
      throw logic_error("Name \"" + names[i] +
                        "\" was not found in names_template");

    const auto idx = distance(names_template.begin(), names_iter);
    ages_sorted.push_back(ages[idx]);
  }

  ages = std::move(ages_sorted);
}
}  // namespace

void NamePairs::readNames() {
  cout << "Enter names one per line. Print \"end\" to stop input." << endl;
  string input;
  getline(cin, input);
  while (input != "end") {
    if (!input.empty()) pNames.push_back(input);
    getline(cin, input);
  }
}

void NamePairs::readAges() {
  cout << "Enter age for each name." << endl;
  for (auto it = pNames.begin(); it != pNames.end(); ++it) {
    cout << *it << ": ";
    double age{};
    cin >> age;
    if (!cin || age < 0) throw InvalidInput{};
    pAges.push_back(age);
  }
}

void NamePairs::sort() {
  vector<string> names_copy = pNames;
  std::sort(pNames.begin(), pNames.end());
  sort_ages(pAges, pNames, names_copy);
}

bool NamePairs::operator==(const NamePairs& other) const {
  if (pNames.size() != other.pNames.size() ||
      pAges.size() != other.pAges.size())
    return false;

  for (size_t i{}; i < pNames.size(); ++i)
    if (pNames[i] != other.pNames[i] || pAges[i] != other.pAges[i])
      return false;

  return true;
}
bool NamePairs::operator!=(const NamePairs& other) const {
  return !(*this == other);
}

std::ostream& operator<<(std::ostream& stream, const NamePairs& object) {
  for (size_t i{}; i < object.getNames().size(); ++i)
    stream << object.getNames()[i] << ": " << object.getAges()[i] << endl;
  return stream;
}