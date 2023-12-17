#include <iostream>
#include <set>
#include <string>

using namespace std;

const char INVALID_TOKEN = '_';

const set<char> specialSymbols = {'!', '~', '&', '^', '(', ')', '.', ';'};

bool isSpecial(char c) {
  return specialSymbols.find(c) != specialSymbols.end();
}

bool isLiteral(char c) { return c == '0' || c == '1' || c >= 'a' && c <= 'z'; }

void error(string const& message) {
  cout << message << endl;
  exit(1);
}

class Token {
  char pKind = INVALID_TOKEN;
  bool pValue = false;

 public:
  explicit Token(char c) : pKind(c), pValue(false) {}
  Token(char c, bool value) : pKind(c), pValue(value) {}
  char kind() const { return pKind; }
  bool value() const { return pValue; }
};

class TokenStream {
  bool pFull;
  Token pBuffer;

 public:
  TokenStream() : pFull(false), pBuffer(INVALID_TOKEN) {}
  Token get() {
    if (pFull) {
      pFull = false;
      return pBuffer;
    }

    char c;
    cin >> c;
    if (isSpecial(c)) return Token(c);
    if (isLiteral(c)) return Token('L', true);
    error("Invalid token");

    // Default value.
    return pBuffer;
  }

  void putback(Token const& t) {
    if (pFull) error("Token buffer is full. Unable to putback");
    pBuffer = t;
    pFull = true;
  }
};

TokenStream ts;

bool expr();

bool primary() {
  Token t = ts.get();
  switch (t.kind()) {
    case '(': {
      bool v = expr();
      t = ts.get();
      if (t.kind() != ')') error("Invalid expression: \')\' expected");
      return v;
    }
    case 'L':
      return t.value();

      // exit
    case ';':
      ts.putback(t);
      return false;
  }
  error("Ptimary expression expected");
  return false;
}

bool term() {
  Token t = ts.get();
  while (true) {
    switch (t.kind()) {
      case '~':
        return expr();
      case '!':
        return expr();
      default:
        ts.putback(t);
        return expr();
    }
  }
  return false;
}

bool expr() {
  bool left = primary();
  Token t = ts.get();
  while (true) {
    switch (t.kind()) {
      case '&':
        left = left && primary();
        t = ts.get();
        break;
      case '^': {
        left = left && primary();
        t = ts.get();
        break;
      }
      default:
        ts.putback(t);
        return left;
    }
  }

  // Should be unreachable. Without this return the function will not compile.
  return false;
}

int main() {
  bool val = false;
  while (cin) {
    Token t = ts.get();
    if (t.kind() == '.') break;
    if (t.kind() == ';')
      cout << boolalpha << val << endl;
    else
      ts.putback(t);
    val = term();
  }
  return 0;
}