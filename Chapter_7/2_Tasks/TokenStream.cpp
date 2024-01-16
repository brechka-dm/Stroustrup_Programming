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
const string varDefineKey =
    "#";  // Keyword changed from "let" to "#" according to task 11.
const string exitKey =
    "exit";  // Keyword changed from "q" to "exit" according to task 12.
const string sqrtKey = "sqrt";
const string powKey = "pow";

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

Token TokenStream::returnNewToken() const {
  char ch;
  cin >> ch;
  const TokenKind kind = charToTokenKind(ch);
  return isAllowedTokenType(kind) ? Token(kind)
         : isNumber(ch)           ? getNumberToken(ch)
                                  : getAlphanumericToken(ch);
}

Token TokenStream::getNumberToken(char c) const {
  cin.putback(c);
  double val;
  cin >> val;
  return Token(TokenKind::number, val);
}

Token TokenStream::getAlphanumericToken(char c) const {
  if (!isalpha(c) && c != '#') error("Incorrect token");
  string s;
  s += c;
  while (cin.get(c) && (isalpha(c) || isdigit(c))) s += c;
  cin.putback(c);
  return s == varDefineKey ? Token(TokenKind::varDefine)
         : s == sqrtKey    ? Token(TokenKind::sqrt)
         : s == powKey     ? Token(TokenKind::pow)
         : s == exitKey    ? Token(TokenKind::exit)
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
  while (cin >> ch)
    if (ch == c) return;
}