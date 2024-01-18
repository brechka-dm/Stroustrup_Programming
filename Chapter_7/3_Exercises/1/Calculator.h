#pragma once

#include "Table.h"
#include "TokenStream.h"
#include "Variable.h"

class Calculator {
  // Added use of the Table class as per exercise 9.
  Table pVarTable;
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
  
 public:
  Calculator();
  void calculate();
  // isConst indicates whether the declared variable is a constant.
  void defineVar(const std::string& varName, double varValue, bool isConst);
  void redefineVar(const std::string& varName, double varValue);
};