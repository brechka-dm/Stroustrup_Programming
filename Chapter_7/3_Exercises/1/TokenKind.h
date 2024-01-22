#pragma once

#include <string>

enum class TokenKind {
  exit,
  answer,
  varName,
  varDefine,
  number,
  openParentesis,
  closeParentesis,
  openBracket,
  closeBracket,
  plus,
  minus,
  multiply,
  division,
  factorial,
  reminder,
  assignment,
  sqrt,
  pow,
  comma,
  alphanumeric,
  constDefine,   // Used for consts definition (Ex 3).
  help,          // Added for Exercise 7.
  exprDelimiter  // Added to separate expressions on the same line, according to
                 // Exercise 8.
};

inline bool isNumber(char c) { return c >= '0' && c <= '9' || c == '.'; }
std::string kindToString(TokenKind kind);
TokenKind charToTokenKind(char c);