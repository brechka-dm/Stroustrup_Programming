#include <string>

#include "Calculator.h"

/*
 * This solution of Exercise 1 from Chapter 8.
 * Added constructor parameters std::istream& input, std::ostream& output for
 * the Calculator class. Also added std::istream& input constructor parameter
 * for TokenStream class. It is pointless to add parameters to the methods
 * expression, term, etc., as suggested in the exercise, because in the current
 * implementation the object of the TokenStream class is a member of the
 * Calculator class. 
 * All unnecessary comments from the program have been removed.
 * Detailed comments can be found in 
 * https://github.com/brechka-dm/Stroustrup_Programming/tree/766d3bf1b3b56dd63bc82b9f2959ac1913518bd4/Chapter_7/2_Tasks
 * and 
 * https://github.com/brechka-dm/Stroustrup_Programming/tree/688ee0d096f55963273a1417c51ec7e3ae38c8c0/Chapter_7/3_Exercises
 */

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::string;

int main() {
  cout << Calculator::helpString << endl;
  Calculator calculator(cin, cout);
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