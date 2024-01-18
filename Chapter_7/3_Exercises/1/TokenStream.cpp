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
const string varDefineKey{kindToString(TokenKind::varDefine)};
const string exitKey{kindToString(TokenKind::exit)};
const string sqrtKey{kindToString(TokenKind::sqrt)};
const string powKey{kindToString(TokenKind::pow)};
const string constDefKey{kindToString(TokenKind::constDefine)};

const unordered_set<TokenKind> brackets{
    TokenKind::openParentesis, TokenKind::closeParentesis,
    TokenKind::openBracket, TokenKind::closeBracket};
const unordered_set<TokenKind> operations{
    TokenKind::plus,     TokenKind::minus,     TokenKind::multiply,
    TokenKind::division, TokenKind::factorial, TokenKind::reminder};
const unordered_set<TokenKind> instructions{TokenKind::answer, TokenKind::exit,
                                            TokenKind::assignment,
                                            TokenKind::comma};

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

Token TokenStream::returnNewToken(){
  char c;
  while (cin.get(c) && isspace(c))
  {
      if(charToTokenKind(c) != TokenKind::answer)
          cin.putback(c);
  }
  const TokenKind kind = charToTokenKind(c);
  return isAllowedTokenType(kind) ? Token(kind)
         : isNumber(c)           ? getNumberToken(c)
                                  : getAlphanumericToken(c);
}

Token TokenStream::getNumberToken(char c) {
  cin.putback(c);
  string s;
  while (cin.get(c) && isdigit(c)) s += c;
  if (charToTokenKind(c) == TokenKind::answer) cin.putback(c);
  return Token(TokenKind::number, stod(s));
}

Token TokenStream::getAlphanumericToken(char c) const {
  // Added support for underscores in variable names as per exercise 1.
  if (!isalpha(c) && c != '#' && c != '_') error("Incorrect token");
  string s;
  s += c;
  while (cin.get(c) && (isalpha(c) || isdigit(c) || c == '_')) s += c;
  cin.putback(c);
  return s == varDefineKey  ? Token(TokenKind::varDefine)
         : s == sqrtKey     ? Token(TokenKind::sqrt)
         : s == powKey      ? Token(TokenKind::pow)
         : s == constDefKey ? Token(TokenKind::constDefine)
         : s == exitKey     ? Token(TokenKind::exit)
                            : Token(TokenKind::varName, s);
}

TokenStream::TokenStream() : pFull(false), pBuffer(TokenKind::exit) {}

Token TokenStream::get() { return pFull ? returnBufer() : returnNewToken(); }

void TokenStream::putback(Token const& t) {
  if (pFull) 
  {
      int c = 0;
      error("Token buffer is full. Unable to putback");
  }
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
  while (cin >> ch)
    if (ch == c) return;
}