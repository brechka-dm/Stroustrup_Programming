#pragma once

#include "TokenTypeFromChar.h"

class Token {
  TokenType pType = TokenType::Invalid;

 public:
  Token() : pType(TokenType::Invalid) {}
  explicit Token(char c) : pType(tokenTypeFromChar(c)) {}
  explicit Token(TokenType type) : pType(type) {}
  Token(char c, bool value) : pType(tokenTypeFromChar(c)) {}
  TokenType getType() const { return pType; }
};