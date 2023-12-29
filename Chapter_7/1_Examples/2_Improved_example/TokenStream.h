#pragma once

#include "Token.h"

class TokenStream {
  bool pFull = false;
  Token pBuffer;

  Token returnBufer();
  Token returnNewToken();
  Token getNumberToken(char c);
  Token getVarToken(char c);

 public:
  TokenStream();
  Token get();

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
};