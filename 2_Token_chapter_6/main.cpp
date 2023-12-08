#include <iostream>

using namespace std;

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
      case ';':
      case 'q':
      case '(':
      case ')':
      case '+':
      case '-':
      case '*':
      case '/':
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
  }
  void putback(Token const& t) {
    if (full) error("Token buffer is full. Unable o putback");
    buffer = t;
    full = true;
  }

 private:
  bool full;
  Token buffer;
};

Token get_token();

double primary() {
  Token t = get_token();
  switch (t.kind) {
    case '(': {
      double d = expression();
      t = get_token();
      if (t.kind != ')') error("Invalid expression: \')\' expected");
      return d;
    }
    case '8':
      return t.value;
    default:
      error("Ptimary expression expected");
  }
}

double term() {
  TokenStream ts;

  double left = primary();
  Token t = ts.get();
  while (true) {
    switch (t.kind) {
      case '*':
        left *= primary();
        t = ts.get();
        break;
      case '/':
        double d = primary();
        if (d == 0) error("Division by zero");
        left /= d;
        t = ts.get();
        break;
      default:
        ts.putback(t);
        return left;
    }
  }
}

double expression() {
  TokenStream ts;

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
}

int main() {
  double val = 0;
  TokenStream ts;

  while (cin) {
    Token t = ts.get();
    if (t.kind == 'q') break;
    if (t.kind == ';')
      cout << "=" << val << endl;
    else
      ts.putback(t);
    val = expression();
  }
}