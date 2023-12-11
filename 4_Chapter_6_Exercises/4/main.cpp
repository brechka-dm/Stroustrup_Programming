#include <iostream>
#include <string>
#include <vector>

using namespace std;

void error(const string& msg) {
  cout << msg;
  exit(1);
}

class NameValue {
  string pName;
  int pValue;

 public:
  NameValue() : pName(""), pValue(0) {}
  NameValue(const string& name, int value) : pName(name), pValue(value) {}
  bool operator==(const NameValue& other) const { return pName == other.pName; }
  void print() const { cout << pName << ": " << pValue << endl; }
};

bool valInContainer(const NameValue& val, const vector<NameValue>& container) {
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