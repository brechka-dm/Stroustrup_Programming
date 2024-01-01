#pragma once

#include <string>
#include <unordered_map>

#include "TokenStream.h"

class Calculator {
  std::unordered_map<std::string, double> pVarTable;
  TokenStream pTokenStream;

  double statement();
  double declaration();
  double expression();
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
  double defineVar(const std::string& varName, double varValue);
};