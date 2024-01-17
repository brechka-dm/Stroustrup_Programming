#pragma once

#include <string>
#include <unordered_map>

#include "TokenStream.h"
#include "Variable.h"

class Calculator {
  std::unordered_map<std::string, Variable> pVarTable;
  TokenStream pTokenStream;
  double statement();
  // isConst indicates whether the declared variable is a constant.
  // An argument with a default value is used see A.9.2.
  double declaration(bool isConst = false);
  double expression();
  double redifinition(const std::string& varName);
  double term();
  double factorialTerm();
  double primary();
  double handleParentesis(TokenKind closeParentesisKind);
  double getVarValue(const std::string& varName);
  void cleanUpMess();
  void setVarValue(const std::string& varName, double varValue);
  bool isVarDeclared(const std::string& varName);

 public:
  Calculator();
  void calculate();
  // isConst indicates whether the declared variable is a constant.
  void defineVar(const std::string& varName, double varValue, bool isConst);
  void redefineVar(const std::string& varName, double varValue);
};