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
  constDefine,   
  help,          
  exprDelimiter  
};

inline bool isNumber(char c) { return c >= '0' && c <= '9' || c == '.'; }
std::string kindToString(TokenKind kind);
TokenKind charToTokenKind(char c);