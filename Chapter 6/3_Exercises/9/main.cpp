#include <iostream>
#include <string>

using namespace std;

/*
 * This program is the solution to Exercise 9 of Chapter 6 of PROGRAMMING.
 * Principles and Practice Using C++. 2nd edition.
 *
 * The program reads digits and composes integers from them. For example, the
 * number 123 is read as a sequence of symbols 1, 2 and 3. The program should
 * display the following message: "123 is 1 hundred, 2 tens and 3 ones.
 */
int main() {
  cout << "Input 1 - 4 digits:" << endl;
  string input;
  getline(cin, input);
  if (!cin || input.empty()) {
    cout << "Incorrect input. Please input 1 - 4 digits." << endl;
    return 1;
  }
  if (input.size() > 4) {
    cout << "Incorrect input. Please input not more than 4 digits." << endl;
    return 1;
  }

  int result = 0;
  string output;
  for (size_t i = 0; i < input.length(); i++) {
    // The first symbol in the string has index 0, but it has the highest index
    // in the number.
    size_t pos = input.length() - i - 1;
    char c = input[i];

    // isdigit checks if char is digit in range [0, 9].
    if (!isdigit(c)) {
      cout << "Incorrect input: \"" << c << "\" is not a digit." << endl;
      return 1;
    }

    switch (pos) {
      case 3:
        // The digits in the ASCII table are sequentially arranged one after the
        // other, starting from 0. To get the value of a digit we subtract the
        // code 0 from the digit code.
        result += static_cast<int>(c - '0') * 1000;
        // string(1, c) converts c to string to be able to use the + operation
        // defined for the string type.
        output += (string(1, c) + " thousands ");
        break;
      case 2:
        result += static_cast<int>(c - '0') * 100;
        output += (string(1, c) + " hundreds ");
        break;
      case 1:
        result += static_cast<int>(c - '0') * 10;
        output += (string(1, c) + " tens ");
        break;
      case 0:
        result += static_cast<int>(c - '0');
        if (!output.empty()) output += "and ";
        output += (string(1, c) + " ones");
        break;
    }
  }
  cout << result << endl << output << endl;
  return 0;
}