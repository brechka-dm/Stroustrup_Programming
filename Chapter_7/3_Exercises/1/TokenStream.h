#pragma once

#include <iostream>

#include "Token.h"

using std::cin;

class TokenStream {
  bool pFull = false;
  Token pBuffer;
  Token returnBufer();
  Token returnNewToken() const;
  Token getNumberToken(char c) const;
  Token getAlphanumericToken(char c) const;
 public:
  TokenStream();
  Token get();
  void putback(Token const& t);
  void ignore(char c);
};