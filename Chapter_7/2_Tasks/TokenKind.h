#pragma once

/*
 * Allowable token types.
 */
enum class TokenKind {
  exit = '`',
  answer = ';',
  varName = '@',
  varDefine = '$',
  number = '#',
  openParentesis = '(',
  closeParentesis = ')',
  openBracket = '{',
  closeBracket = '}',
  plus = '+',
  minus = '-',
  multiply = '*',
  divide = '/',
  factorial = '!',
  reminder = '%',
  assignment = '=',
  
  sqrt = 's',
  pow = 'p',

  // Used to indicate unknown token kind.
  alphanumeric = 'a'
};

/*
 * Returns true if c is a number.
 */
inline bool isNumber(char c) { return c >= '0' && c <= '9' || c == '.'; }

/*
 * Convets TokenKind to its char representation.
 */
inline char kindToChar(TokenKind kind) { return static_cast<char>(kind); }

/*
 * Converts c to TokenKind.
 */
inline TokenKind charToTokenKind(char c) {
  switch (c) {
    case 'q':
    case '`':
      return TokenKind::exit;
    case ';':
      return TokenKind::answer;
    case '@':
      return TokenKind::varName;
    case '$':
      return TokenKind::varDefine;
    case '#':
      return TokenKind::number;
    case '(':
      return TokenKind::openParentesis;
    case ')':
      return TokenKind::closeParentesis;
    case '{':
      return TokenKind::openBracket;
    case '}':
      return TokenKind::closeBracket;
    case '+':
      return TokenKind::plus;
    case '-':
      return TokenKind::minus;
    case '*':
      return TokenKind::multiply;
    case '/':
      return TokenKind::divide;
    case '!':
      return TokenKind::factorial;
    case '%':
      return TokenKind::reminder;
    case '=':
      return TokenKind::assignment;
  }
  if (isNumber(c)) return TokenKind::number;

  return TokenKind::alphanumeric;
}