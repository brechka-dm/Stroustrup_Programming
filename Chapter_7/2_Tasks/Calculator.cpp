#include "Calculator.h"

#include <cmath>
#include <iostream>
#include <numeric>
#include <string>

#include "Error.h"

using ::std::cerr;
using std::cout;
using std::endl;
using std::exception;
using std::string;
using std::to_string;

namespace {
const char prompt = '>';

// Calculates factorial from arg.
// If arg < 0 or arg is fractional throws error.
// Also throws error in case of result type overflow.
double factorial(double arg) {
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

double calcSqrt(double x) {
  if (x < 0) error("Unable to calc square root from \"" + to_string(x) + "\"");
  return sqrt(x);
}
}  // namespace

double Calculator::statement() {
  Token t = pTokenStream.get();
  switch (t.getKind()) {
    case TokenKind::varDefine:
      return declaration();
    default:
      pTokenStream.putback(t);
      return expression();
  }
}
double Calculator::declaration() {
  Token t = pTokenStream.get();
  if (t.getKind() != TokenKind::varName)
    error("\"name\" is expected in declaration");
  string varName = t.getName();
  t = pTokenStream.get();
  if (t.getKind() != TokenKind::assignment)
    error("\"=\" missed in declaration of \"varName\"");
  double d = expression();
  defineVar(varName, d);
  return d;
}
double Calculator::expression() {
  double left = term();
  Token t = pTokenStream.get();

  // Using while to be able to handle expressions of the form x+y-z...
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

double Calculator::term() {
  double left = factorialTerm();
  Token t = pTokenStream.get();

  // Using while to be able to handle expressions of the form x*y/z...
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
        return left;
        break;
      }
      case TokenKind::sqrt:
        t = pTokenStream.get();
        if (t.getKind() != TokenKind::openParentesis)
          error("Error in \"sqrt\": \"(\" expected");
        left = calcSqrt(primary());
        t = pTokenStream.get();
        if (t.getKind() != TokenKind::closeParentesis)
          error("Error in \"sqrt\": \")\" expected");
        t = pTokenStream.get();
        break;
      case TokenKind::pow: {
        t = pTokenStream.get();
        if (t.getKind() != TokenKind::openParentesis)
          error("Error in \"pow\": \"(\" expected");
        double num{primary()};
        t = pTokenStream.get();
        if (t.getKind() != TokenKind::comma)
          error("Error in \"pow\": \",\" expected");
        double deg{primary()};
        int intDeg = static_cast<int>(deg);
        if (deg != intDeg) error("Error in \"pow\": degree should be integer");
        left = pow(num, deg);
        if (t.getKind() != TokenKind::closeParentesis)
          error("Error in \"pow\": \")\" expected");
        t = pTokenStream.get();
        break;
      }
      default:
        pTokenStream.putback(t);
        return left;
    }
  }
  return -1;
}
double Calculator::factorialTerm() {
  Token t = pTokenStream.get();
  if (t.getKind() == TokenKind::factorial) return factorial(primary());
  pTokenStream.putback(t);
  return primary();
}
double Calculator::primary() {
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
      return getVarValue(t.getName());
    case TokenKind::exit:
      pTokenStream.putback(t);
    case TokenKind::sqrt:
      pTokenStream.putback(t);
      break;
    case TokenKind::pow:
      pTokenStream.putback(t);
      break;
    default:
      error("Ptimary expression expected");
  }
  return -1;
}
double Calculator::handleParentesis(TokenKind closeParentesisKind) {
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
double Calculator::getVarValue(const std::string& varName) {
  if (!isVarDeclared(varName))
    error("get: \"" + varName + "\" variable is undefined");
  return pVarTable[varName];
}
void Calculator::cleanUpMess() {
  pTokenStream.ignore(kindToChar(TokenKind::answer));
}
void Calculator::setVarValue(const std::string& varName, double varValue) {
  if (isVarDeclared(varName)) pVarTable[varName] = varValue;
  error("set: \"" + varName + "\" variable is undefined");
}
bool Calculator::isVarDeclared(const std::string& varName) {
  return pVarTable.find(varName) != pVarTable.end();
}
Calculator::Calculator() : pTokenStream() {}
void Calculator::calculate() {
  while (cin) {
    // Using try... catch to handle exceptions manualy.
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
void Calculator::defineVar(const std::string& varName, double varValue) {
  if (isVarDeclared(varName))
    error("Variable \"" + varName + "\" is declared twice");
  pVarTable[varName] = varValue;
}
