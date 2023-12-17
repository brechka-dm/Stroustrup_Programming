#include <iostream>
#include <set>
#include <string>

#include "Token.h"

using namespace std;

void error(string const& message) {
  cout << message << endl;
  exit(1);
}

class TokenStream {
  bool pFull;
  Token pBuffer;
  string pString;
  int pCounter;

 public:
  TokenStream()
      : pFull(false), pBuffer(TokenType::Invalid), pString(), pCounter(0) {}
  TokenStream(const string& str)
      : pFull(false), pBuffer(TokenType::Invalid), pString(str), pCounter(0) {}

  Token get() {
    if (pFull) {
      pFull = false;
      pCounter++;
      return pBuffer;
    }

    if (pCounter >= pString.size()) {
      return Token(TokenType::EndOfString);
    }

    return Token(pString[pCounter++]);
  }

  void putback(Token const& t) {
    if (pFull) error("Token buffer is full. Unable to putback");
    pBuffer = t;
    pFull = true;
    pCounter--;
  }
};

TokenStream ts;

bool expr();
bool term();

bool primary() {
  Token t = ts.get();
  switch (t.getType()) {
    case TokenType::OpenParenthesis: {
      bool v = term();
      t = ts.get();
      if (t.getType() != TokenType::CloseParenthesis)
        error("Invalid expression: \')\' expected");
      return v;
    }
    case TokenType::Literal:
      return true;
    case TokenType::EndOfString:
      return false;
    default:
      return false;
  }
  error("Ptimary expression expected");
  return false;
}

bool term() {
  Token t = ts.get();
  while (true) {
    switch (t.getType()) {
      case TokenType::Extension:
        return expr();
      case TokenType::Inversion:
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
    switch (t.getType()) {
      case TokenType::Conjunction:
        left = left && primary();
        t = ts.get();
        break;
      case TokenType::Disjunction: {
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

class Recognizer {
  TokenStream pTokenStream;

 public:
  // Recognizer(string const& str) :pTokenStream(str){}
  bool recognize(string const& str) {
    ts = TokenStream(str);
    return term();
  }
};

int main() {
  string str;
  getline(cin, str);
  Recognizer r;
  cout << boolalpha << r.recognize(str) << endl;
  return 0;
}