#include "LogicGrammarRecognizer.h"

#include "Error.h"

using namespace std;

bool LogicGrammarRecognizer::primaryExpression() {
  Token t = pTokenStream.get();
  switch (t.getType()) {
    case TokenType::OpenParenthesis: {
      bool v = term();
      t = pTokenStream.get();
      if (t.getType() != TokenType::CloseParenthesis)
        error();
      return v;
    }
    case TokenType::Literal:
      return true;
    case TokenType::EndOfString:
      return false;
    default:
      return false;
  }
  error();
  return false;
}

bool LogicGrammarRecognizer::expression() {
  bool left = primaryExpression();
  Token t = pTokenStream.get();
  while (true) {
    switch (t.getType()) {
      case TokenType::Conjunction:
        left = left && primaryExpression();
        t = pTokenStream.get();
        break;
      case TokenType::Disjunction:
        left = left && primaryExpression();
        t = pTokenStream.get();
        break;
      case TokenType::EndOfString:
        return left;
      default:
        pTokenStream.putback(t);
        return false;
    }
  }

  // Should be unreachable. Without this return the function will not compile.
  return false;
}

bool LogicGrammarRecognizer::term() {
  Token t = pTokenStream.get();
  switch (t.getType()) {
    case TokenType::Extension:
      return expression();
    case TokenType::Inversion:
      return expression();
    default:
      pTokenStream.putback(t);
      return expression();
  }
  return false;
}

LogicGrammarRecognizer::LogicGrammarRecognizer() : pTokenStream() {}

bool LogicGrammarRecognizer::recognize(const std::string& str) {
  pTokenStream.init(str);
  return term();
}