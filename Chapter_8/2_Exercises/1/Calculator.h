#pragma once

#include "Table.h"
#include "TokenStream.h"
#include "Variable.h"

class Calculator {
  Table pVarTable;
  std::istream& pInput;
  std::ostream& pOutput;
  TokenStream pTokenStream;
  double statement();
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
  
 public:
  Calculator(std::istream& input, std::ostream& output);
  void calculate();
  void defineVar(const std::string& varName, double varValue, bool isConst);
  void redefineVar(const std::string& varName, double varValue);
  static const std::string helpString;
};