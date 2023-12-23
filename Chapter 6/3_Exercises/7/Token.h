#pragma once

#include "TokenTypeFromChar.h"

/*
 * This class recognizes the type of token by its char representation.
 */
class Token {
  // Initial value.
  TokenType pType = TokenType::Invalid;

 public:
  Token() : pType(TokenType::Invalid) {}
  explicit Token(char c) : pType(tokenTypeFromChar(c)) {}
  explicit Token(TokenType type) : pType(type) {}
  TokenType getType() const { return pType; }
};