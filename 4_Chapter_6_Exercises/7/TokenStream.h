#pragma once

#include <string>

#include "Token.h"
#include "TokenType.h"

class TokenStream {
  Token pBuffer;
  std::string pString;
  int pCounter = 0;
  bool pFull = false;

 public:
  TokenStream();
  void init(const std::string& str);
  Token get();
  void putback(Token const& t);
};