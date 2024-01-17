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

const string welcomeString{R"'(Welcome to the calculator program!
Please enter expressions containing floating point numbers.
You can use next operations to create expressions: 
"+", "-", "*", "/", "!", "{", "}" "(", ")" and functions sqrt() and pow().
Also you can define variables:
# x=6 
Type ";" to get answer.
Type "exit" to quit.)'"};

int main() {
  cout << welcomeString << endl;
  Calculator calculator;
  while (cin) {
    try {
      calculator.defineVar("pi", 3.1415926535, true);
      calculator.defineVar("e", 2.7182818284, true);
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