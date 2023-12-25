#include <iostream>
#include <string>

using namespace std;

/*
 * This program is a fulfillment of exercise 3 from Chapter 6.
 * Adding the ability to calculate factorial.
 */

// Use this const instead of quit proposed in the book.
const char EXIT_INSTRUCTION = 'x';
// Use this const instead of print proposed in the book.
const char ANSWER_INSTRUCTION = '=';
const char PROMPT = '>';
const string WELCOME_STRING =
    "Welcome to the calculator program!\n"
    "Please enter expressions containing floating point numbers.\n"
    "You can use \"+\", \"-\", \"*\", \"/\", \"!\" and \"(\", \")\" to create "
    "expression.\n"
    "Press \"=\" to get answer.\n"
    "Press \"x\" to exit program.";

void error(string const& message) {
  cout << message << endl;
  exit(1);
}

// This fuinction calculates factorial.
double factorial(double arg) {
  if (arg < 0)
    error("Unable to calculate factorial from \"" + to_string(arg) + "\"");
  int intArg = int(arg);
  // We can only calculate the factorial from an integer. If arg has a
  // fractional part, the difference will be greater than zero (we use a small
  // number close to zero to avoid calculation accuracy errors, see
  // Chapter 11.2.4).
  if (arg - intArg > 0.00001)
    error("Unable to calculate factorial from \"" + to_string(arg) + "\"");

  if (intArg == 0 || intArg == 1) return 1.0;

  // Use iterations instead of recursion to calc factorial.
  double result = 1.0;
  for (int i = 1; i <= intArg; i++) {
    result *= i;
    if (result < 0)
      error("Unable to calculate factorial from \"" + to_string(arg) +
            "\". The result is too big.");
  }
  return result;
}

class Token {
 public:
  char kind;
  double value;

  Token(char ch) : kind(ch), value(0.0) {}
  Token(char ch, double val) : kind(ch), value(val) {}
};

class TokenStream {
 public:
  TokenStream() : full(false), buffer(0) {}
  Token get() {
    if (full) {
      full = false;
      return buffer;
    }

    char ch;
    cin >> ch;
    switch (ch) {
      case ANSWER_INSTRUCTION:
      case EXIT_INSTRUCTION:
      case '(':
      case ')':
      case '+':
      case '-':
      case '*':
      case '/':
      case '{':
      case '}':
      case '!':
      case '%':
        return Token(ch);
      case '.':
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9': {
        cin.putback(ch);
        double val;
        cin >> val;
        return Token('8', val);
      }
      default:
        error("Incorrect token");
    }

    return Token('0');
  }

  void putback(Token const& t) {
    if (full) error("Token buffer is full. Unable to putback");
    buffer = t;
    full = true;
  }

 private:
  bool full;
  Token buffer;
};

TokenStream ts;

double expression();

double primary() {
  Token t = ts.get();
  switch (t.kind) {
    case '(': {
      double d = expression();
      t = ts.get();
      if (t.kind != ')') error("Invalid expression: \')\' expected");
      return d;
    }
    case '{': {
      double d = expression();
      t = ts.get();
      if (t.kind != '}') error("Invalid expression: \'}\' expected");
      return d;
    }
    case '8':
      return t.value;
    case '-':
      return -primary();
    case '+':
      return primary();

    // This case added to correctly handle 'x' instruction.
    case EXIT_INSTRUCTION:
      ts.putback(t);

      // Default return value. Not analyzed by the program.
      return -1;
    default:
      error("Ptimary expression expected");
  }

  // Should be unreachable. Without this return the function will not compile.
  return -1;
}

// Add this term to grammar to handle factorial.
double factorial_term() {
  double left = primary();
  Token t = ts.get();
  if (t.kind == '!') return factorial(left);
  ts.putback(t);
  return left;
}

double term() {
  double left = factorial_term();
  Token t = ts.get();
  while (true) {
    switch (t.kind) {
      case '*':
        left *= factorial_term();
        t = ts.get();
        break;
      case '/': {
        double d = factorial_term();
        if (d == 0) error("Division by zero");
        left /= d;
        t = ts.get();
        break;
      }
      case '%': {
        double d = primary();
        // For some reason, the narrow_cast proposed in the book doesn't work.
        int i1 = static_cast<int>(left);
        if (i1 != left) error("Left \'%\' operand is not integer");
        int i2 = static_cast<int>(d);
        if (i2 != d) error("Right \'%\' operand is not integer");
        if (i2 == 0) error("Division by zero");
        left = i1 % i2;
        t = ts.get();
        break;
      }
      default:
        ts.putback(t);
        return left;
    }
  }

  return -1;
}

double expression() {
  double left = term();
  Token t = ts.get();
  while (true) {
    switch (t.kind) {
      case '+':
        left += term();
        t = ts.get();
        break;
      case '-':
        left -= term();
        t = ts.get();
        break;
      default:
        ts.putback(t);
        return left;
    }
  }

  // Should be unreachable. Without this return the function will not compile.
  return -1;
}

int main() {
  double val = 0;

  cout << WELCOME_STRING << endl;

  try {
    while (cin) {
      cout << PROMPT;
      Token t = ts.get();
      while (t.kind == ANSWER_INSTRUCTION) t = ts.get();
      if (t.kind == EXIT_INSTRUCTION) return 0;
      ts.putback(t);
      cout << expression() << endl;
    }
  } catch (exception& e) {
    cerr << e.what() << endl;
    return 1;
  } catch (...) {
    cerr << "exception \n";
    return 2;
  }
  return 0;
}