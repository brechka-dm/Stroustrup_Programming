#pragma once

#include <iostream>

#include "Token.h"

using std::cin;

class TokenStream {
  std::istream& pInput;
  Token pBuffer;
  bool pFull = false;
  Token returnBufer();
  Token returnNewToken();
  Token getNumberToken(char c);
  Token getAlphanumericToken(char c) const;
 public:
  TokenStream(std::istream& input);
  Token get();
  void putback(Token const& t);
  void ignore(char c);
};