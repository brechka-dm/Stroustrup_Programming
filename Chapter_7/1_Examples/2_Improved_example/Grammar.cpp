#include "Grammar.h"

#include <numeric>
#include <string>

#include "Error.h"
#include "TokenKinds.h"

using std::string;
using std::to_string;

double Grammar::factorial(double arg) {
  if (arg < 0)
    error("Unable to calculate factorial from \"" + to_string(arg) + "\"");
  int intArg = int(arg);
  if (arg - intArg > 0.00001)
    error("Unable to calculate factorial from \"" + to_string(arg) + "\"");

  if (intArg == 0 || intArg == 1) return 1.0;

  double result = 1.0;
  for (int i = 1; i <= intArg; i++) {
    result *= i;
    if (result < 0)
      error("Unable to calculate factorial from \"" + to_string(arg) +
            "\". The result is too big.");
  }
  return result;
}

double Grammar::primary() {
  Token t = pTokenStream.get();
  switch (t.getKind()) {
    case '(':
      return handleParentesis(')');
    case '{':
      return handleParentesis('}');
    case TokenKinds::number:
      return t.getValue();
    case '-':
      return -primary();
    case '+':
      return primary();
    case TokenKinds::varName:
      return getValue(t.getName());
    case TokenKinds::exit:
      pTokenStream.putback(t);
    default:
      error("Ptimary expression expected");
  }
  return -1;
}

double Grammar::handleParentesis(char closeParentesisType) {
  double d = expression();
  Token t = pTokenStream.get();
  if (t.getKind() != closeParentesisType) {
    string errorMsg = "Invalid expression: \'";
    errorMsg += closeParentesisType;
    errorMsg += "\' expected";
    error(errorMsg);
  }
  return d;
}

double Grammar::factorialTerm() {
  double left = primary();
  Token t = pTokenStream.get();
  if (t.getKind() == '!') return factorial(left);
  pTokenStream.putback(t);
  return left;
}

double Grammar::term() {
  double left = factorialTerm();
  Token t = pTokenStream.get();
  while (true) {
    switch (t.getKind()) {
      case '*':
        left *= factorialTerm();
        t = pTokenStream.get();
        break;
      case '/': {
        double d = factorialTerm();
        if (d == 0) error("Division by zero");
        left /= d;
        t = pTokenStream.get();
        break;
      }
      case '%': {
        double d = primary();
        int i1 = static_cast<int>(left);
        if (i1 != left) error("Left \'%\' operand is not integer");
        int i2 = static_cast<int>(d);
        if (i2 != d) error("Right \'%\' operand is not integer");
        if (i2 == 0) error("Division by zero");
        left = i1 % i2;
        t = pTokenStream.get();
        break;
      }
      default:
        pTokenStream.putback(t);
        return left;
    }

    return -1;
  }

  double Grammar::expression() {
    double left = term();
    Token t = ts.get();
    while (true) switch (t.kind) {
        case '+':
          left += term();
          t = ts.get();
          break;
        case '-':
          left -= term();
          t = ts.get();
          break;
        default:
          ts.putback(t);
          return left;
      }

    // Should be unreachable. Without this return the function will not compile.
    return -1;
  }

  void Grammar::cleanUpMess() { pTokenStream.ignore(TokenKinds::answer); }

  double Grammar::getVarValue(const std::string& varName) {
    if (!isVarDeclared(varName))
      error("get: \"" + varName + "\" variable is undefined");
    return varTable[varName];
  }

  void Grammar::setVarValue(const std::string& varName, double varValue) {
    if (isVarDeclared(varName)) varTable[varName] = varValue;

    error("set: \"" + varName + "\" variable is undefined");
  }

  bool Grammar::isVarDeclared(const std::string& varName) {
    return varTable.find(varName) != varTable.end()
  }

  double Grammar::defineVar(const std::string& varName, double varValue) {
    if (isVarDeclared(varValue))
      error("Variable \"" + varValue + "\" is declared twice");
    varTable[varName] = arValue;
    return val;
  }