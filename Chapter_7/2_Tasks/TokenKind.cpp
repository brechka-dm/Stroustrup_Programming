#include "TokenKind.h"

#include <string>
#include <vector>

using std::string;
using std::vector;

struct TokenKindValue {
  const TokenKind kind;
  const string value;
};

const vector<TokenKindValue> tokenKinds{{TokenKind::exit, "exit"},
                                        {TokenKind::answer, ";"},
                                        {TokenKind::varName, "@"},
                                        {TokenKind::varDefine, "#"},
                                        {TokenKind::number, "$"}};