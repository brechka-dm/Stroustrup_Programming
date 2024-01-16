#pragma once

#include <iostream>

#include "Token.h"

using std::cin;

/*
 * Provides reading tokens from the user input.
 */
class TokenStream {
  // Indicates if any token stores in the buffer.
  bool pFull = false;

  // Stroes token that added by putback method.
  Token pBuffer;

  // Returns stored token.
  Token returnBufer();

  // Reads token from the user input.
  Token returnNewToken() const;

  // Reads number from the user input to create a token of number type.
  Token getNumberToken(char c) const;

  // Reads string from the user input to create a token of var, var define, sqrt
  // or pow type.
  Token getAlphanumericToken(char c) const;

 public:
  TokenStream();

  // Returns token from the stream.
  // If there is a token stored in the buffer, it will be returned, otherwise a
  // new token is read from the user input.
  Token get();

  // Stores token t in stream buffer.
  void putback(Token const& t);

  // Forces to ignore character c in the user input.
  void ignore(char c);
};