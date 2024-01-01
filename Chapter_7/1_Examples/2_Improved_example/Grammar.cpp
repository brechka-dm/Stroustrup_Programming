#include "Grammar.h"

#include <numeric>
#include <string>

#include "Error.h"

using std::string;
using std::to_string;

double Grammar::statement() {
  Token t = pTokenStream.get();
  switch (t.getKind()) {
    case TokenKind::varDefine:
      return declaration();
    default:
      pTokenStream.putback(t);
      return expression();
  }
}
double Grammar::declaration() {
  Token t = pTokenStream.get();
  if (t.getKind() != TokenKind::varName)
    error("\"name\" is expected in declaration");
  string varName = t.getName();
  Token t2 = pTokenStream.get();
  if (t2.getKind() != TokenKind::assignment)
    error("\"=\" missed in declaration of \"varName\"");
  double d = expression();
  defineVar(varName, d);
  return d;
}
double Grammar::expression() {
  double left = term();
  Token t = pTokenStream.get();
  while (true) switch (t.getKind()) {
      case TokenKind::plus:
        left += term();
        t = pTokenStream.get();
        break;
      case TokenKind::minus:
        left -= term();
        t = pTokenStream.get();
        break;
      default:
        pTokenStream.putback(t);
        return left;
    }

  // Should be unreachable. Without this return the function will not compile.
  return -1;
}

double Grammar::term() {
  double left = factorialTerm();
  Token t = pTokenStream.get();
  while (true) {
    switch (t.getKind()) {
      case TokenKind::multiply:
        left *= factorialTerm();
        t = pTokenStream.get();
        break;
      case TokenKind::divide: {
        double d = factorialTerm();
        if (d == 0) error("Division by zero");
        left /= d;
        t = pTokenStream.get();
        break;
      }
      case TokenKind::reminder: {
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
}
double Grammar::factorialTerm() {
  double left = primary();
  Token t = pTokenStream.get();
  if (t.getKind() == TokenKind::factorial) return factorial(left);
  pTokenStream.putback(t);
  return left;
}
double Grammar::primary() {
  Token t = pTokenStream.get();
  switch (t.getKind()) {
    case TokenKind::openParentesis:
      return handleParentesis(TokenKind::closeParentesis);
    case TokenKind::openBracket:
      return handleParentesis(TokenKind::closeBracket);
    case TokenKind::number:
      return t.getValue();
    case TokenKind::minus:
      return -primary();
    case TokenKind::plus:
      return primary();
    case TokenKind::varName:
      return getValue(t.getName());
    case TokenKind::exit:
      pTokenStream.putback(t);
    default:
      error("Ptimary expression expected");
  }
  return -1;
}

double Grammar::handleParentesis(TokenKind closeParentesisKind) {
  double d = expression();
  Token t = pTokenStream.get();
  if (t.getKind() != closeParentesisKind) {
    string errorMsg = "Invalid expression: \'";
    errorMsg += kindToChar(closeParentesisKind);
    errorMsg += "\' expected";
    error(errorMsg);
  }
  return d;
}

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

  bool Grammar::isVarDeclared(const std::string& varName){
      return varTable.find(varName) != varTable.end()}

  Grammar::Grammar()
      : pTokenStream() {}
  void Grammar::inputText() {
    while (cin) {
      try {
        cout << prompt;
        Token t = pTokenStream.get();
        while (t.getKind() == TokenKind::answer) t = pTokenStream.get();
        if (t.getKind() == TokenKind::exit) return;
        pTokenStream.putback(t);
        cout << "=" << statement() << endl;
      } catch (exception& e) {
        cerr << e.what() << endl;
        cleanUpMess();
      }
    }
  }
  double Grammar::defineVar(const std::string& varName, double varValue) {
    if (isVarDeclared(varValue))
      error("Variable \"" + varValue + "\" is declared twice");
    varTable[varName] = arValue;
    return val;
  }
