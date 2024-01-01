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
const string varDefineKey = "let";
const string exitKey = "quit";

const unordered_set<TokenKind> brackets{
    TokenKind::openParentesis, TokenKind::closeParentesis,
    TokenKind::openBracket, TokenKind::closeBracket};
const unordered_set<TokenKind> operations{
    TokenKind::plus,   TokenKind::minus,     TokenKind::multiply,
    TokenKind::divide, TokenKind::factorial, TokenKind::reminder};
const unordered_set<TokenKind> instructions{TokenKind::answer, TokenKind::exit};

const unordered_set<char> generateNumberChars() {
  unordered_set<char> result;
  for (char c = '0'; c <= '9'; c++) result.insert(c);
  result.insert('.');
  return result;
}

const unordered_set<char> numberChars(generateNumberChars());

bool isAllowedTokenType(TokenKind kind) {
  return brackets.find(kind) == brackets.end() &&
                 operations.find(kind) == operations.end() &&
                 instructions.find(kind) == instructions.end()
             ? false
             : true;
}

bool isNumberToken(char c) { return numberChars.find(c) != numberChars.end(); }
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
         : isNumberToken(ch)      ? getNumberToken(ch)
                                  : getVarToken(ch);
}

Token TokenStream::getNumberToken(char c) const {
  cin.putback(c);
  double val;
  cin >> val;
  return Token(TokenKind::number, val);
}

Token TokenStream::getVarToken(char c) const {
  if (!isalpha(c)) error("Incorrect token");
  string s;
  s += c;
  while (cin.get(c) && (isalpha(c) || isdigit(c))) s += c;
  cin.putback(c);
  return s == varDefineKey ? Token(TokenKind::varDefine)
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
  const char bufferChar = kindToChar(pBuffer.getKind());
  if (pFull && c == bufferChar) {
    pFull = false;
    return;
  }
  char ch = 0;
  while (cin >> ch)
    if (ch == c) return;
}