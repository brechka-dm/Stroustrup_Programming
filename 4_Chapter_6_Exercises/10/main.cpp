#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

class CalcException : public runtime_error {
 public:
  CalcException(const string& msg) : runtime_error(msg) {}
};

void fractionalReduction(vector<int>& numerator, vector<int>& denomenator0,
                         vector<int>& denomenator1) {
  using Iter = std::vector<int>::const_iterator;

  std::vector<int> toRemove;
  for (Iter iter = denomenator0.begin(); iter != denomenator0.end(); iter++) {
    Iter numeratorIter = find(numerator.begin(), numerator.end(), *iter);
    if (numeratorIter != numerator.end()) {
      numerator.erase(numeratorIter);
      toRemove.push_back(*iter);
    }
  }

  for (int i : toRemove)
    denomenator0.erase(std::remove(denomenator0.begin(), denomenator0.end(), i),
                       denomenator0.end());

  if (denomenator1.empty()) return;

  for (int& num : numerator)
    for (int& den : denomenator1)
      if (num > 1 && den > 1 && num % den == 0) {
        num = num / den;
        den = 1;
        break;
      }

  return;
}

int fraction(vector<int>& numerator, vector<int>& denomenator0,
             vector<int>& denomenator1) {
  int num =
      accumulate(numerator.begin(), numerator.end(), 1, std::multiplies<int>());
  int den = accumulate(denomenator0.begin(), denomenator0.end(), 1,
                       std::multiplies<int>()) *
            accumulate(denomenator1.begin(), denomenator1.end(), 1,
                       std::multiplies<int>());
  return num / den;
}

vector<int> generateVector(int n) {
  vector<int> result(n);
  iota(result.begin(), result.end(), 1);
  return result;
}

int permutation(int a, int b) {
  if (a < b) throw CalcException("\"a\" should be not less then \"b\"");
  vector<int> numerator(generateVector(a));
  vector<int> denomenator(generateVector(a - b));
  vector<int> emptyVector;
  fractionalReduction(numerator, denomenator, emptyVector);
  return fraction(numerator, denomenator, emptyVector);
}

int combination(int a, int b) {
  if (a < b) throw CalcException("\"a\" should be not less then \"b\"");
  vector<int> numerator(generateVector(a));
  vector<int> denomenator0(generateVector(a - b));
  vector<int> denomenator1(generateVector(b));
  fractionalReduction(numerator, denomenator0, denomenator1);
  return fraction(numerator, denomenator0, denomenator1);
}

bool getParams(int argc, char** argv, int& a, int& b) {
  if (argc < 4) {
    cout << "Not enough parameters." << endl;
    return false;
  }
  try {
    a = stoi(argv[2]);
    b = stoi(argv[3]);

    float aF = stof(argv[2]);
    float bF = stof(argv[3]);

    bool aIsInteger = aF - a <= 0;
    bool bIsInteger = bF - b <= 0;
    if (!aIsInteger || !bIsInteger) {
      cout << "a and b should be integer" << endl;
      return false;
    }
  } catch (const exception) {
    cout << "Unable to convert \"" << argv[2] << "\" or \"" << argv[3]
         << "\" to int." << endl;
    return false;
  }

  if (a < b) {
    cout << "a should be not less then b" << endl;
    return false;
  }

  if (a < 0 || b < 0) {
    cout << "a and b should be not negative" << endl;
    return false;
  }
  return true;
}

int main(int argc, char** argv) {
  string help(
      "Ex10 -c|-p|-h a b\n"
      "-c - calculate combination\n"
      "-p - calculate permutation\n"
      "-h - show help\n"
      "a and b should be integer");

  if (argc < 2 || strlen(argv[1]) < 2) {
    cout << help;
    return 1;
  }

  if (argv[1][1] != 'c' && argv[1][1] != 'p' && argv[1][1] != 'h') {
    cout << "Invalid operation" << endl;
    cout << help;
    return 1;
  }

  int a, b;
  if (!getParams(argc, argv, a, b)) {
    cout << help;
    return 1;
  }
  try {
    switch (argv[1][1]) {
      case 'c':
        cout << combination(a, b);
        break;
      case 'p':
        cout << permutation(a, b);
        break;
      default:
        cout << help;
    }
  } catch (exception& e) {
    cout << e.what() << endl;
    return 1;
  }
  return 0;
}