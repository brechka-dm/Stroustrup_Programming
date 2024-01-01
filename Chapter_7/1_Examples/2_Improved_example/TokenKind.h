#pragma once

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
  assignment = '='
};

inline char kindToChar(TokenKind kind) { return static_cast<char>(kind); }
inline TokenKind charToTokenKind(char c) {
  switch (c) {
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
  // Handle unknown characters or return a special value for such cases
  // For example, you can return TokenKind::unknown or throw an exception.
  // In this example, I'll return TokenKind::exit for unknown characters.
  return TokenKind::exit;
}