#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

/*
 * This program is the solution to Exercise 10 of Chapter 6 of PROGRAMMING.
 * Principles and Practice Using C++. 2nd edition.
 *
 * The program allows to count the number of permutations or combinations of two
 * numbers entered by the user.
 *
 * The calculating formulas use the ratio of factorials. The value of the
 * factorial grows very fast and can cause memory overflow, so we try to reduce
 * as many unnecessary multipliers as possible before direct calculations.
 */

/*
 * This is a user defined exception. See Chapter 5.6.
 */
class CalcException : public runtime_error {
 public:
  CalcException(const string& msg) : runtime_error(msg) {}
};

/*
 * A formula that calculates permutations or combinations contains a factorial
 * in the numerator and one or two factorials in the denominator. We pass to
 * this function the multipliers included in the factorials as vectors of
 * integers. The function reduces the number of multipliers, excluding those
 * that will be reduced when calculating the ratio.
 */
void fractionalReduction(vector<int>& numerator, vector<int>& denomenator0,
                         vector<int>& denomenator1) {
  // See iteratot definition in Chapter 20.
  // using here is the analog of typedef, see chapter 19.4.2.
  using Iter = std::vector<int>::const_iterator;

  // The next section is aimed for removing identical multipliers in the
  // numerator and denominator0.
  std::vector<int> toRemove;
  for (Iter iter = denomenator0.begin(); iter != denomenator0.end(); iter++) {
    Iter numeratorIter = find(numerator.begin(), numerator.end(), *iter);
    if (numeratorIter != numerator.end()) {
      // Remove number from numerator and put the corresponding number in the
      // vector of deletions from the denominator0.
      numerator.erase(numeratorIter);
      toRemove.push_back(*iter);
    }
  }

  for (int i : toRemove)
    denomenator0.erase(std::remove(denomenator0.begin(), denomenator0.end(), i),
                       denomenator0.end());

  // denomenator1 may be empty.
  if (denomenator1.empty()) return;

  // Go through the remaining numbers in the numerator and try to reduce them by
  // the numbers in the denominator1.
  for (int& num : numerator)
    for (int& den : denomenator1)
      if (num > 1 && den > 1 && num % den == 0) {
        num = num / den;
        den = 1;
        break;
      }

  return;
}

/*
 * A formula that calculates permutations or combinations contains a factorial
 * in the numerator and one or two factorials in the denominator.
 * This function calculates the value of a fraction.
 * The number of permutations and combinations is always an integer, so this
 * function is of type int.
 */
int fraction(vector<int>& numerator, vector<int>& denomenator0,
             vector<int>& denomenator1) {
  // Use accumulate to calc multiplication of all numbers in vector. See
  // Chapter 21.5.2.
  int num =
      accumulate(numerator.begin(), numerator.end(), 1, std::multiplies<int>());
  int den = accumulate(denomenator0.begin(), denomenator0.end(), 1,
                       std::multiplies<int>()) *
            accumulate(denomenator1.begin(), denomenator1.end(), 1,
                       std::multiplies<int>());
  return num / den;
}

/*
 * This function generates factorial multipliers (from 1 to n).
 */
vector<int> generateVector(int n) {
  vector<int> result(n);
  // Use std::itoa to fill the vector with an increasing sequence of numbers.
  // See https://en.cppreference.com/w/cpp/algorithm/iota
  iota(result.begin(), result.end(), 1);
  return result;
}

/*
 * This function counts the number of permutations. The number of permutations
 * is always an integer, so the function is of type int.
 */
int permutation(int a, int b) {
  // Throws exception in case of a < b.
  if (a < b) throw CalcException("\"a\" should be not less then \"b\"");
  vector<int> numerator(generateVector(a));
  vector<int> denomenator(generateVector(a - b));
  // The permutation formula has only one factorial in denomenator, but
  // functions fractionalReduction and fraction has three arguments. So we have
  // to pass the empty vector as the third argument.
  vector<int> emptyVector;
  fractionalReduction(numerator, denomenator, emptyVector);
  return fraction(numerator, denomenator, emptyVector);
}

/*
 * This function counts the number of combinations. The number of combinations
 * is always an integer, so the function is of type int.
 */
int combination(int a, int b) {
  if (a < b) throw CalcException("\"a\" should be not less then \"b\"");
  vector<int> numerator(generateVector(a));
  vector<int> denomenator0(generateVector(a - b));
  vector<int> denomenator1(generateVector(b));
  fractionalReduction(numerator, denomenator0, denomenator1);
  return fraction(numerator, denomenator0, denomenator1);
}

/*
 * We use argc and argv to get user input (see
 * https://www.geeksforgeeks.org/command-line-arguments-in-c-cpp/).
 * This function tries to get numbers a and b needed to calculate permutations
 * and combinations from user input. The function provides for error handling.
 * If errors are detected, the function returns false. If no errors are
 * detected, the function returns true and arguments a and b will contain the
 * values entered by the user.
 */
bool getParams(int argc, char** argv, int& a, int& b) {
  // Correct input must contain 4 parameters.
  if (argc < 4) {
    cout << "Not enough parameters." << endl;
    return false;
  }
  // Use try ... catch instruction to catch possible errors when converting
  // strings to numbers.
  try {
    // stof converts string to number (may throw exception).
    float aF = stof(argv[2]);
    float bF = stof(argv[3]);

    // A and b must be integer. But the user can enter non-integer numbers,
    // which is an error. We check for the non-integer part of the number by
    // creating a new variable with the non-integer part discarded, then
    // calculate the difference between the original and the new variable. If
    // the difference is not zero, then the original value was not an integer.
    int a = static_cast<int>(aF);
    int b = static_cast<int>(bF);

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
  // To use program user should enter program name, one of possible operation
  // keys (c, p, h) and two integer numbers (in case of keys c and p). Total of
  // 4 arguments.
  string help(
      "Ex10 -c|-p|-h a b\n"
      "-c - calculate combination\n"
      "-p - calculate permutation\n"
      "-h - show help\n"
      "a and b should be integer");

  // If there are less than two arguments, it is an error.
  if (argc < 2 || strlen(argv[1]) < 2) {
    cout << help;
    return 1;
  }

  // Operation key is a string of two chars. We need to analyze the second char.
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

  // Use try ... catch as combination and permutation may throw exception.
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