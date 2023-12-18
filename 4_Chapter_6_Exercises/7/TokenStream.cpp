#include "TokenStream.h"

#include "Error.h"

using namespace std;

TokenStream::TokenStream()
    : pBuffer(TokenType::Invalid), pString(), pCounter(0), pFull(false) {}

void TokenStream::init(const string& str) {
  pString = str;
  pBuffer = Token(TokenType::Invalid);
  pCounter = 0;
  pFull = false;
}

Token TokenStream::get() {
  if (pFull) {
    pFull = false;
    pCounter++;
    return pBuffer;
  }

  if (pCounter >= pString.size()) return Token(TokenType::EndOfString);

  return Token(pString[pCounter++]);
}

void TokenStream::putback(Token const& t) {
  if (pFull) error();
  pBuffer = t;
  pFull = true;
  pCounter--;
}