#include <iostream>
#include <string>

using namespace std;

/*
 * This program is a fulfillment of exercise 2 from Chapter 6.
 * Adding the ability to handle brackets {}.
 */

const char EXIT_INSTRUCTION = 'x';
const char ANSWER_INSTRUCTION = '=';
const string WELCOME_STRING =
    "Welcome to the calculator program!\n"
    "Please enter expressions containing floating point numbers.\n"
    "You can use \"+\", \"-\", \"*\", \"/\" and \"(\", \")\" to create expression.\n"
    "Press \"=\" to get answer.\n"
    "Press \"x\" to exit program.";

void error(string const& message) {
  cout << message << endl;
  exit(1);
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

double term() {
  double left = primary();
  Token t = ts.get();
  while (true) {
    switch (t.kind) {
      case '*':
        left *= primary();
        t = ts.get();
        break;
      case '/': {
        double d = primary();
        if (d == 0) error("Division by zero");
        left /= d;
        t = ts.get();
        break;
      }
      default:
        ts.putback(t);
        return left;
    }
  }

  // Should be unreachable. Without this return the function will not compile.
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

  while (cin) {
    Token t = ts.get();
    if (t.kind == EXIT_INSTRUCTION) break;
    if (t.kind == ANSWER_INSTRUCTION)
      cout << "=" << val << endl;
    else
      ts.putback(t);
    val = expression();
  }

  return 0;
}