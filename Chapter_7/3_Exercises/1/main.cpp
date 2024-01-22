#include <string>

#include "Calculator.h"

/*
 * This program extends
 * https://github.com/brechka-dm/Stroustrup_Programming/tree/766d3bf1b3b56dd63bc82b9f2959ac1913518bd4/Chapter_7/2_Tasks
 * to solve Exercises 1, 2, 3, 5, 7, 8, and 9 from Chapter 7. The program
 * retains only the comments related to these exercises.
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