#pragma once

#include <string>

/*
 * Allowable token types.
 */
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
  alphanumeric  // Used to indicate unknown token kind.
};

/*
 * Returns true if c is a number.
 */
inline bool isNumber(char c) { return c >= '0' && c <= '9' || c == '.'; }

/*
 * Convets TokenKind to its string representation.
 * Returns an empty string if representation is not found.
 */
std::string kindToString(TokenKind kind);

/*
 * Converts c to TokenKind.
 * Returns TokenKind::alphanumeric in case no kind corresponding to c.
 */
TokenKind charToTokenKind(char c);