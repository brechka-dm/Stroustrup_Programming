#pragma once

#include <string>

#include "TokenKind.h"

/*
 * A token is an element of a grammar. It can be a numeric value, a variable, or
 * a symbol allowed in the grammar.
 */
class Token {
  // Used for variables.
  std::string pName;

  // Used for variables and numeric values.
  double pValue{0.0};
  TokenKind pKind{TokenKind::exit};

 public:
  Token(TokenKind kind) : pValue{0.0}, pKind(kind) {}
  Token(TokenKind kind, double val) : pValue(val), pKind(kind) {}
  Token(TokenKind kind, std::string n) : pName(n), pValue{0.0}, pKind(kind) {}

  TokenKind getKind() const { return pKind; }
  double getValue() const { return pValue; }
  const std::string& getName() const { return pName; }
};