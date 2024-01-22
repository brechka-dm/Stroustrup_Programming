#include "TokenStream.h"

#include <iostream>
#include <numeric>
#include <string>
#include <unordered_set>

#include "Error.h"

using std::cin;
using std::iota;
using std::string;
using std::unordered_set;

namespace {
const unordered_set<TokenKind> brackets{
    TokenKind::openParentesis, TokenKind::closeParentesis,
    TokenKind::openBracket, TokenKind::closeBracket};
const unordered_set<TokenKind> operations{
    TokenKind::plus,     TokenKind::minus,     TokenKind::multiply,
    TokenKind::division, TokenKind::factorial, TokenKind::reminder};
const unordered_set<TokenKind> instructions{
    TokenKind::answer, TokenKind::exit, TokenKind::assignment,
    TokenKind::comma,  TokenKind::help, TokenKind::exprDelimiter};

bool isAllowedTokenType(TokenKind kind) {
  return brackets.find(kind) == brackets.end() &&
                 operations.find(kind) == operations.end() &&
                 instructions.find(kind) == instructions.end()
             ? false
             : true;
}
}  // namespace

Token TokenStream::returnBufer() {
  pFull = false;
  return pBuffer;
}

Token TokenStream::returnNewToken() {
  char c;
  // Read the stream ignoring whitespace characters. But if answer(\n) is
  // encountered, the token of Answer type returns. TokenKind::answer = '\n'
  // according to Exercise 5.
  while (cin.get(c) && isspace(c)) {
    if (charToTokenKind(c) == TokenKind::answer)
      return Token(TokenKind::answer);
  }
  const TokenKind kind = charToTokenKind(c);
  return isAllowedTokenType(kind) ? Token(kind)
         : isNumber(c)            ? getNumberToken(c)
                                  : getAlphanumericToken(c);
}

Token TokenStream::getNumberToken(char c) {
  cin.putback(c);
  string s;
  // Read the stream as long as the digits and '.'.
  while (cin.get(c) && (isdigit(c) || c == '.')) s += c;
  // The last read character is returned back to the stream so that it can be
  // processed in the next call returnNewToken.
  cin.putback(c);
  double val = 0;
  // We use stod to convert a string to a number. If the string is not converted
  // to a number stod throws an exception, which we catch.
  try {
    val = stod(s);
  } catch (...) {
    error("\"" + s + "\" is not a number");
  }
  return Token(TokenKind::number, val);
}

Token TokenStream::getAlphanumericToken(char c) const {
  // Added support for underscores in variable names as per Exercise 1.
  if (!isalpha(c) && c != '#' && c != '_') error("Incorrect token");
  string s;
  s += c;
  while (cin.get(c) && (isalpha(c) || isdigit(c) || c == '_')) s += c;
  cin.putback(c);
  return s == kindToString(TokenKind::varDefine) ? Token(TokenKind::varDefine)
         : s == kindToString(TokenKind::sqrt)    ? Token(TokenKind::sqrt)
         : s == kindToString(TokenKind::pow)     ? Token(TokenKind::pow)
         : s == kindToString(TokenKind::constDefine)
             ? Token(TokenKind::constDefine)
         : s == kindToString(TokenKind::exit) ? Token(TokenKind::exit)
         : s == kindToString(TokenKind::help) ? Token(TokenKind::help)
                                              : Token(TokenKind::varName, s);
}

TokenStream::TokenStream() : pFull(false), pBuffer(TokenKind::exit) {}

Token TokenStream::get() { return pFull ? returnBufer() : returnNewToken(); }

void TokenStream::putback(Token const& t) {
  if (pFull) error("Token buffer is full. Unable to putback");
  pBuffer = t;
  pFull = true;
}

void TokenStream::ignore(char c) {
  const std::string bufferString = kindToString(pBuffer.getKind());
  if (pFull && c == bufferString[0]) {
    pFull = false;
    return;
  }
  char ch = 0;
  // Use cin.get to avoid missing the '\n' character.
  while (cin.get(ch))
    if (ch == c) return;
}