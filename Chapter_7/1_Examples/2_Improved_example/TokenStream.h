#pragma once

#include <iostream>

#include "Token.h"

using std::cin;

template <typename T>
class TokenStream {
  bool pFull = false;
  Token<T> pBuffer;

  Token<T> returnBufer() const {
    pFull = false;
    return pBuffer;
  }

  Token<T> returnNewToken() const {
    char ch;
    cin >> ch;
    return isAllowedTokenType(ch) ? Token(ch)
           : isNumberToken(ch)    ? getNumberToken(ch)
                                  : getVarToken(ch);
  }
  Token<T> getNumberToken(char c) {
    cin.putback(c);
    double val;
    cin >> val;
    return Token<T>(numberType, val);
  }
  Token<T> getVarToken(char c);

 public:
  TokenStream();
  Token<T> get();
  void putback(Token<T> const& t);
  void ignore(char c);
};