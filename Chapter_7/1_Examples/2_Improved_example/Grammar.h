#pragma once

#include <string>

#include "TokenStream.h"

class Grammar {
  TokenStream pTokenStream;

  double statement();
  double declaration();
  double expression();
  double term();
  double factorialTerm();
  double primary();
  double handleParentesis(TokenKind closeParentesisKind);
  
  double getValue(const std::string& n);
  double factorial(double arg);

  
  
  

  void cleanUpMess();
  double getVarValue(const std::string& varName);
  void setVarValue(const std::string& varName, double varValue);
  bool isVarDeclared(const std::string& varName);

 public:
  Grammar();
  void inputText();
  double defineVar(const std::string& varName, double varValue);
};