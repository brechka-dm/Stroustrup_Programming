#include "TokenStream.h"

#include <iostream>
#include <numeric>
#include <string>
#include <unordered_set>

#include "Error.h"

using std::cin;
using std::itoa;
using std::string;
using std::unordered_set;

namespace {
const char prompt = '>';
const char answerInstructionType = ';';
const char exitInstructionType = '`';
const char varNameType = '@';
const char varDefineType = '$';
const char numberType = '#';

const string varDefineKey = "let";
const string exitKey = "quit";

const unordered_set<char> brackets{'(', ')', '{', '}'};
const unordered_set<char> operations{'+', '-', '*', '/', '!', '%'};
const unordered_set<char> instructions{answerInstructionType,
                                       exitInstructionType};

const unordered_set<char> generateNumberChars() {
  unordered_set<char> result(10);
  iota(result.begin(), result.end(), 0);
  result.insert('.');
  return result;
}

const unordered_set<char> numberChars(generateNumberChars());

bool isAllowedTokenType(char c) {
  return brackets.find(c) == brackets.end() &&
                 operations.find(c) == operations.end() &&
                 instructions.find(c) == instructions.end()
             ? false
             : true;
}

bool isNumberToken(char c) { return numberChars.find(c) != numberChars.end(); }
}  // namespace

Token TokenStream::returnBufer() {
  pFull = false;
  return pBuffer;
}

Token TokenStream::returnNewToken() {
  char ch;
  cin >> ch;
  return isAllowedTokenType(ch) ? Token(ch)
         : isNumberToken(ch)    ? getNumberToken(ch)
                                : getVarToken(ch);
}

Token TokenStream::getNumberToken(char c) {
  cin.putback(c);
  double val;
  cin >> val;
  return Token(numberType, val);
}

Token TokenStream::getVarToken(char c) {
  if (!isalpha(c)) error("Incorrect token");
  string s;
  s += c;
  while (cin.get(c) && (isalpha(c) || isdigit(c))) s += c;
  cin.putback(c);
  return s == varDefineKey ? Token(varDefineType) : Token(varNameType, s);
}

TokenStream::TokenStream() : pFull(false), pBuffer(0) {}

Token TokenStream::get() { return pFull ? returnBufer() : returnNewToken(); }