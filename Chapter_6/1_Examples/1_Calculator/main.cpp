#include <iostream>

using namespace std;

/*
 * This program contains the calculator program code shown in the examples in
 * Chapters 6.3-6.7. The code contains some stylistic changes and bug fixes.
 */

int main() {
  cout << "Input the expression (+, -, * and / allowed): ";
  int l_val = 0;
  int r_val;
  char operation;

  cin >> l_val;
  if (!cin) {
    cout << "No first operand" << endl;
    return 0;
  };
  while (cin >> operation) {
    // This if is fixing error in the book.
    // Show result when '=' is entered.
    if (operation == '=') {
      cout << l_val << endl;
      return 0;
    }
    cin >> r_val;
    if (!cin) {
      cout << "No second operand" << endl;
      return 0;
    }
    switch (operation) {
      case '+':
        l_val += r_val;
        break;
      case '-':
        l_val -= r_val;
        break;
      case '*':
        l_val *= r_val;
        break;
      case '/':
        l_val /= r_val;
        break;
    }
  }
  cout << "Incorrect expression" << endl;
  return 0;
}