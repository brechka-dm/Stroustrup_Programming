#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

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

double fraction(vector<int>& numerator, vector<int>& denomenator0,
                vector<int>& denomenator1) {
  int num =
      accumulate(numerator.begin(), numerator.end(), 1, std::multiplies<int>());
  int den = accumulate(denomenator0.begin(), denomenator0.end(), 1,
                       std::multiplies<int>()) *
            accumulate(denomenator1.begin(), denomenator1.end(), 1,
                       std::multiplies<int>());
  return static_cast<double>(num) / den;
}

vector<int> generateVector(int n) {
  vector<int> result(n);
  iota(result.begin(), result.end(), 1);
  return result;
}

void printVector(const vector<int>& v) {
  cout << "{ ";
  for (const int n : v) cout << n << " ";
  cout << "}" << endl;
}

void printAll(const vector<vector<int>>& vs) {
  cout << "Numerator: ";
  printVector(vs[0]);
  cout << "denomenator0: ";
  printVector(vs[1]);
  cout << "denomenator1: ";
  printVector(vs[2]);
}

int permutation(int a, int b) {
  vector<int> numerator(generateVector(a));
  vector<int> denomenator(generateVector(a - b));
  fractionalReduction(numerator, denomenator, {});
  return fraction(numerator, denomenator, {});
}

int combination(int a, int b) {
  vector<int> numerator(generateVector(a));
  vector<int> denomenator0(generateVector(a - b));
  vector<int> denomenator1(generateVector(b));
  fractionalReduction(numerator, denomenator0, denomenator1);
  return fraction(numerator, denomenator0, denomenator1);
}

bool getParams(int argc, char** argv, int& a, int& b)
{
  if (argc < 4) return false;
  
}

int main(int argc, char** argv) {
  string help(
      "Ex10 -c|-p|-h a b\n"
      "-c - calculate combination\n"
      "-p - calculate permutation\n"
      "-h - show help\n"
      "a and b should be integer");

  if (argc < 2) cout << help;
  if (strlen(argv[1]) < 2) cout << help;
  switch (argv[1][1]) {
    case 'c':
      return;
    case 'p':
      return;
    default:
      cout << help;
  }
  return 0;
}