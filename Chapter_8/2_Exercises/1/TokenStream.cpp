#include "TokenStream.h"

#include <iostream>
#include <numeric>
#include <string>
#include <unordered_set>

#include "Error.h"

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
  while (pInput.get(c) && isspace(c)) {
    if (charToTokenKind(c) == TokenKind::answer)
      return Token(TokenKind::answer);
  }
  const TokenKind kind = charToTokenKind(c);
  return isAllowedTokenType(kind) ? Token(kind)
         : isNumber(c)            ? getNumberToken(c)
                                  : getAlphanumericToken(c);
}

Token TokenStream::getNumberToken(char c) {
  pInput.putback(c);
  string s;
  while (pInput.get(c) && (isdigit(c) || c == '.')) s += c;
  pInput.putback(c);
  double val = 0;
  try {
    val = stod(s);
  } catch (...) {
    error("\"" + s + "\" is not a number");
  }
  return Token(TokenKind::number, val);
}

Token TokenStream::getAlphanumericToken(char c) const {
  if (!isalpha(c) && c != '#' && c != '_') error("Incorrect token");
  string s;
  s += c;
  while (pInput.get(c) && (isalpha(c) || isdigit(c) || c == '_')) s += c;
  pInput.putback(c);
  return s == kindToString(TokenKind::varDefine) ? Token(TokenKind::varDefine)
         : s == kindToString(TokenKind::sqrt)    ? Token(TokenKind::sqrt)
         : s == kindToString(TokenKind::pow)     ? Token(TokenKind::pow)
         : s == kindToString(TokenKind::constDefine)
             ? Token(TokenKind::constDefine)
         : s == kindToString(TokenKind::exit) ? Token(TokenKind::exit)
         : s == kindToString(TokenKind::help) ? Token(TokenKind::help)
                                              : Token(TokenKind::varName, s);
}

TokenStream::TokenStream(std::istream& input)
    : pInput(input), pBuffer(TokenKind::exit), pFull(false) {}

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
   while (pInput.get(ch))
    if (ch == c) return;
}