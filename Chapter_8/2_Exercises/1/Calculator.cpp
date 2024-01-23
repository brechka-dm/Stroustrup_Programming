#include "Calculator.h"

#include <cmath>
#include <iostream>
#include <numeric>
#include <string>

#include "Error.h"

using ::std::cerr;
using std::endl;
using std::exception;
using std::string;
using std::to_string;

namespace {
const char prompt = '>';

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
    case TokenKind::constDefine:
      return declaration(true);
    default:
      pTokenStream.putback(t);
      return expression();
  }
}
double Calculator::declaration(bool isConst) {
  Token t = pTokenStream.get();
  if (t.getKind() != TokenKind::varName)
    error("\"name\" is expected in declaration");
  string varName = t.getName();
  t = pTokenStream.get();
  if (t.getKind() != TokenKind::assignment)
    error("\"=\" missed in declaration of \"" + varName + "\"");
  double d = expression();
  defineVar(varName, d, isConst);
  return d;
}
double Calculator::expression() {
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

  return -1;
}
double Calculator::redifinition(const std::string& varName) {
  double d = expression();
  redefineVar(varName, d);
  return d;
}
double Calculator::term() {
  double left = factorialTerm();
  Token t = pTokenStream.get();

  while (true) {
    switch (t.getKind()) {
      case TokenKind::multiply:
        left *= factorialTerm();
        t = pTokenStream.get();
        break;
      case TokenKind::division: {
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
        double num{expression()};
        t = pTokenStream.get();
        if (t.getKind() != TokenKind::comma)
          error("Error in \"pow\": \",\" expected");
        double deg{expression()};
        int intDeg = static_cast<int>(deg);
        if (deg != intDeg) error("Error in \"pow\": degree should be integer");
        left = pow(num, deg);
        t = pTokenStream.get();
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
    case TokenKind::varName: {
      const string varName{t.getName()};
      t = pTokenStream.get();
      if (t.getKind() == TokenKind::assignment) return redifinition(varName);
      pTokenStream.putback(t);
      return getVarValue(varName);
    }
    case TokenKind::exit:
    case TokenKind::sqrt:
    case TokenKind::pow:
    case TokenKind::help:
      pTokenStream.putback(t);
      break;
    default:
      error("Primary expression expected");
  }
  return -1;
}
double Calculator::handleParentesis(TokenKind closeParentesisKind) {
  double d = expression();
  Token t = pTokenStream.get();
  if (t.getKind() != closeParentesisKind) {
    string errorMsg = "Invalid expression: \'";
    errorMsg += kindToString(closeParentesisKind);
    errorMsg += "\' expected";
    error(errorMsg);
  }
  return d;
}
double Calculator::getVarValue(const std::string& varName) {
  return pVarTable.get(varName);
}
void Calculator::cleanUpMess() {
  pTokenStream.ignore(kindToString(TokenKind::answer)[0]);
}
void Calculator::setVarValue(const std::string& varName, double varValue) {
  pVarTable.set(varName, varValue);
}
Calculator::Calculator(std::istream& input, std::ostream& output)
    : pInput(input), pOutput(output), pTokenStream(input) {}

void Calculator::calculate() {
  std::vector<double> results;
  while (pInput) {
    try {
      pOutput << prompt;
      Token t = pTokenStream.get();
      while (t.getKind() == TokenKind::answer ||
             t.getKind() == TokenKind::exprDelimiter)
        t = pTokenStream.get();
      pTokenStream.putback(t);
      double result = statement();
      t = pTokenStream.get();
      switch (t.getKind()) {
        case TokenKind::answer:
          results.push_back(result);
          pOutput << "=" << results[0];
          for (int i = 1; i < results.size(); ++i) pOutput << "; " << results[i];
          pOutput << endl;
          results.clear();
          break;
        case TokenKind::exprDelimiter:
          results.push_back(result);
          break;
        case TokenKind::exit:
          return;
        case TokenKind::help:
          pOutput << helpString << endl;
          results.clear();
          continue;
        default:
          error("Invalid expression");
      }
    } catch (exception& e) {
      cerr << e.what() << endl;
      cleanUpMess();
      results.clear();
    }
  }
}
void Calculator::defineVar(const std::string& varName, double varValue,
                           bool isConst) {
  pVarTable.define(varName, varValue, isConst);
}
void Calculator::redefineVar(const std::string& varName, double varValue) {
  pVarTable.redefine(varName, varValue);
}

const std::string Calculator::helpString{R"'(Welcome to the calculator program!
Please enter expressions containing floating point numbers.
You can use next operations to create expressions: 
"+", "-", "*", "/", "!", "{", "}" "(", ")" and functions sqrt() and pow().
Also you can define variables:
# x=6 
Type ";" to get answer.
Type "exit" to quit.)'"};