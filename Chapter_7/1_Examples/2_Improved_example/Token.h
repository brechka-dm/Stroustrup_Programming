#pragma once

#include "TokenKind.h"

#include <string>

class Token {
  std::string pName;
  double pValue{0.0};
  TokenKind pKind{0};

 public:
  Token(TokenKind kind) : pValue{0.0}, pKind(kind) {}
  Token(TokenKind kind, double val) : pValue(val), pKind(kind) {}
  Token(TokenKind kind, std::string n) : pName(n), pValue{0.0}, pKind(kind) {}

  TokenKind getKind() const { return pKind; }
  double getValue() const { return pValue; }
  const std::string& getName() const { return pName; }
};