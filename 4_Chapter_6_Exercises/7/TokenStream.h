#pragma once

#include <string>

#include "Token.h"
#include "TokenType.h"

/*
 * This class is initialized with a string, allows you to select the next
 * character from the string, and define the token type corresponding to that
 * character.
 */
class TokenStream {
  Token pBuffer;
  std::string pString;
  int pCounter = 0;
  bool pFull = false;

 public:
  TokenStream();
  void init(const std::string& str);

  // Returns next token from pString.
  Token get();

  // Stores t in pBuffer.
  void putback(Token const& t);
};