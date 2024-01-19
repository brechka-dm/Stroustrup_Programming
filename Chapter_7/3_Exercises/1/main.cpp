#include <string>

#include "Calculator.h"

/*
 * This program is improved implementation of the Calculator presented in
 * Chapter 7. In this implementation, individual program components are placed
 * in separate files.
 */

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::string;

int main() {
  cout << Calculator::helpString << endl;
  Calculator calculator;
  while (cin) {
    try {
      calculator.calculate();
      return 0;
    } catch (std::exception& e) {
      cerr << e.what() << endl;
      return 1;
    } catch (...) {
      cerr << "exception \n";
      return 2;
    }
  }
  return 0;
}