#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
 * This program is the solution to Exercise 4 of Chapter 6 of PROGRAMMING.
 * Principles and Practice Using C++. 2nd edition.
 * The program takes as input a set of pairs consisting of a name
 * and a value, e.g. Joe 17 and Barbara 22. Input stops when the string NoName 0
 * is entered. If the name is entered twice, the program displays an error
 * message. When input is complete, the program prints all pairs (name, score)
 * one per line. The NameValue class is used to store the data. The class is
 * storing the string and the value.
 */

/*
 * This is analogous to the function error used in the book.
 */
void error(const string& msg) {
  cout << msg;

  // Using exit to terminate program with return value of 1.
  exit(1);
}

class NameValue {
  string pName;
  int pValue;

 public:
  NameValue() : pName(""), pValue(0) {}
  NameValue(const string& name, int value) : pName(name), pValue(value) {}
  // Use this method to print values.
  void print() const { cout << pName << ": " << pValue << endl; }
  // This is an overloading of the = operator to be able to compare NameValue
  // objects with each other (See Chapter 9.6). In this case, the comparison is
  // done by the pName field.
  bool operator==(const NameValue& other) const { return pName == other.pName; }
};

/*
 * Returns true if val is inside container.
 */
bool valInContainer(const NameValue& val, const vector<NameValue>& container) {
  // See Chapter 21.2.
  const auto containerIter = find(container.begin(), container.end(), val);
  return containerIter != container.end();
}

int main() {
  vector<NameValue> data;
  string name;
  int val = 0;
  while (true) {
    cin >> name;

    // cin.fail described in Chapter 10.
    if (cin.fail()) error("Incorrect name");
    cin >> val;
    if (cin.fail()) error("Incorrect value");

    if (name == "NoName" && val == 0) break;

    NameValue obj(name, val);
    if (valInContainer(obj, data)) {
      cout << "Name \"" << name << "\" already in container" << endl;
      continue;
    }
    data.push_back(obj);
  }

  for (const NameValue& item : data) item.print();
  return 0;
}