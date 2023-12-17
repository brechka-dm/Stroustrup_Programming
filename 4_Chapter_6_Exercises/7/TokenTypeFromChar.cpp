#include "TokenTypeFromChar.h"

bool isLiteral(char c) { return c == '0' || c == '1' || c >= 'a' && c <= 'z'; }

TokenType tokenTypeFromChar(char c) {
  if (isLiteral(c)) return TokenType::Literal;
  switch (c) {
    case '!':
      return TokenType::Inversion;
    case '~':
      return TokenType::Extension;
    case '&':
      return TokenType::Conjunction;
    case '^':
      return TokenType::Disjunction;
    case '\n':
      return TokenType::EndOfString;
    case '(':
      return TokenType::OpenParenthesis;
    case ')':
      return TokenType::CloseParenthesis;
  }

  return TokenType::Invalid;
}