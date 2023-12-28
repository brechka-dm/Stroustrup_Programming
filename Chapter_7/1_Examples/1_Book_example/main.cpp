#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
 * This program is a corrected and extended code of the examples presented in
* Chapter 7. Additions not mentioned in the book are annotated.
*
* This program is an extended version of the calculator, allowing the use of
* variables. Improved handling of errors and exceptional situations added.
 */

// Ude this const instead of "result" proposed in the book.
const char EXIT_INSTRUCTION = 'q';
// Use this const instead of "print" proposed in the book.
const char ANSWER_INSTRUCTION = ';';
const char PROMPT = '>';
// Use "#" instead of "a" proposed in the book.
const char name = '#';
// Use "$" instead of "L" proposed in the book.
const char let = '$';

const string declkey = "let";

const string WELCOME_STRING =
    "Welcome to the calculator program!\n"
    "Please enter expressions containing floating point numbers.\n"
    "You can use \"+\", \"-\", \"*\", \"/\", \"!\" and \"(\", \")\" to create "
    "expression.\n"
    "Press \"=\" to get answer.\n"
    "Press \"q\" to exit program.";

void error(string const& message) {
  throw runtime_error(message);
  exit(1);
}

// Forward declaration.
double getValue(string n);

double factorial(double arg) {
  if (arg < 0)
    error("Unable to calculate factorial from \"" + to_string(arg) + "\"");
  int intArg = int(arg);
  if (arg - intArg > 0.00001)
    error("Unable to calculate factorial from \"" + to_string(arg) + "\"");

  if (intArg == 0 || intArg == 1) return 1.0;

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
  string name;

  Token(char ch) : kind(ch), value(0.0) {}
  Token(char ch, double val) : kind(ch), value(val) {}
  Token(char ch, string n) : kind(ch), name(n) {}
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
      // To be able to assign values to variables.
      case '=':
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
        if (isalpha(ch)) {
          string s;
          s += ch;
          while (cin.get(ch) && (isalpha(ch) || isdigit(ch))) s += ch;
          cin.putback(ch);
          if (s == declkey) return Token(let);
          return Token(name, s);
        }
        error("Incorrect token");
    }

    return Token('0');
  }

  void putback(Token const& t) {
    if (full) error("Token buffer is full. Unable to putback");
    buffer = t;
    full = true;
  }
  void ignore(char c) {
    if (full && c == buffer.kind) {
      full = false;
      return;
    }
    char ch = 0;
    while (cin >> ch)
      if (ch == c) return;
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
    // To get variable value
    case name:
      return getValue(t.name);

      // This case added to correctly handle 'q' instruction.
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

void cleanUpMess() { ts.ignore(ANSWER_INSTRUCTION); }

class Variable {
 public:
  string name;
  double value;
  Variable(string n, double v) : name(n), value(v) {}
};

vector<Variable> varTable;

double getValue(string n) {
  for (size_t i = 0; i < varTable.size(); i++)
    if (varTable[i].name == n) return varTable[i].value;
  error("get: \"n\" variable is undefined");

  // Default value.
  return -1;
}

void setValue(const string& n, double v) {
  for (size_t i = 0; i < varTable.size(); i++)
    if (varTable[i].name == n) {
      varTable[i].value = v;
      return;
    }
  error("set: \"n\" variable is undefined");
}

bool isDeclared(string var) {
  for (int i = 0; i < varTable.size(); ++i)
    if (varTable[i].name == var) return true;
  return false;
}

double defineName(string var, double val) {
  if (isDeclared(var)) error("Variable \"" + var + "\" is declared twice");
  varTable.push_back(Variable(var, val));
  return val;
}

double declaration() {
  Token t = ts.get();
  if (t.kind != name) error("\"name\" is expected in declaration");
  string varName = t.name;
  Token t2 = ts.get();
  if (t2.kind != '=') error("\"=\" missed in declaration of \"varName\"");
  double d = expression();
  defineName(varName, d);
  return d;
}

double statement() {
  Token t = ts.get();
  switch (t.kind) {
    case let:
      return declaration();
    default:
      ts.putback(t);
      return expression();
  }
}

void calculate() {
  while (cin) {
    try {
      cout << PROMPT;
      Token t = ts.get();
      while (t.kind == ANSWER_INSTRUCTION) t = ts.get();
      if (t.kind == EXIT_INSTRUCTION) return;
      ts.putback(t);
      cout << "=" << statement() << endl;
    } catch (exception& e) {
      cerr << e.what() << endl;
      cleanUpMess();
    }
  }
}

int main() {
  double val = 0;

  cout << WELCOME_STRING << endl;

  while (cin) {
    try {
      defineName("pi", 3.1415926535);
      defineName("e", 2.7182818284);
      calculate();
      return 0;
    } catch (exception& e) {
      cerr << e.what() << endl;
      return 1;
    } catch (...) {
      cerr << "exception \n";
      return 2;
    }
  }
  return 0;
}