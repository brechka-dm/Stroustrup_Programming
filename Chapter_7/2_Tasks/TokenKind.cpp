#include "TokenKind.h"

#include <string>
#include <vector>

using std::find_if;
using std::string;
using std::vector;

namespace {
struct TokenKindValue {
  const TokenKind kind;
  const string value;
};
const vector<TokenKindValue> tokenKinds{
    {TokenKind::exit, "exit"},
    {TokenKind::answer, ";"},
    {TokenKind::varName, "@"},
    {TokenKind::varDefine, "#"},
    {TokenKind::number, "$"},
    {TokenKind::openParentesis, "("},
    {TokenKind::closeParentesis, ")"},
    {TokenKind::openBracket, "{"},
    {TokenKind::closeBracket, "}"},
    {TokenKind::plus, "+"},
    {TokenKind::minus, "-"},
    {TokenKind::multiply, "*"},
    {TokenKind::division, "/"},
    {TokenKind::factorial, "!"},
    {TokenKind::reminder, "%"},
    {TokenKind::assignment, "="},
    {TokenKind::sqrt, "sqrt"},
    {TokenKind::pow, "pow"},
    {TokenKind::comma, ","},
    {TokenKind::alphanumeric, "~"}  // Used to indicate unknown token kind.

};
}  // namespace

std::string kindToString(TokenKind kind) {
  // Using std::find_if see chapter 21.3.
  // Using lambda-function as argument, see
  // https://en.cppreference.com/w/cpp/language/lambda
  const auto iter = find_if(
      tokenKinds.begin(), tokenKinds.end(),
      [kind](const TokenKindValue& record) { return record.kind == kind; });
  return iter != tokenKinds.end() ? iter->value : "";
}

TokenKind charToTokenKind(char c) {
  if (isNumber(c)) return TokenKind::number;
  const auto iter =
      find_if(tokenKinds.begin(), tokenKinds.end(),
              [strC = string(1, c)](const TokenKindValue& record) {
                return record.value == strC;
              });
  return iter != tokenKinds.end() ? iter->kind : TokenKind::alphanumeric;
}