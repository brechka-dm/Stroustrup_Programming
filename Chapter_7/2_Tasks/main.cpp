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

const string welcomeString =
    "Welcome to the calculator program!\n"
    "Please enter expressions containing floating point numbers.\n"
    "You can use \"+\", \"-\", \"*\", \"/\", \"!\" and \"(\", \")\" to create "
    "expression.\n"
    "Press \";\" to get answer.\n"
    "Press \"q\" to exit program.";

int main() {
  cout << welcomeString << endl;

  // The calculator is implemented as a separate class.
  Calculator calculator;
  while (cin) {
    try {
      calculator.defineVar("pi", 3.1415926535);
      calculator.defineVar("e", 2.7182818284);
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