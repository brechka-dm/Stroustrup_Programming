#pragma once

#include <string>
#include <unordered_map>

#include "TokenStream.h"

/*
 * This class recognizes the grammar of expressions and performs calculations.
 */
class Calculator {
  // Stores declared variables.
  std::unordered_map<std::string, double> pVarTable;

  // Used to get token from user input.
  TokenStream pTokenStream;

  // Used for reading variable declarations or entering expressions.
  double statement();

  // Used to declare variables.
  double declaration();

  // Used to enter expressions.
  double expression();

  double redifinition(const std::string& varName);

  // The result of the operation of division, multiplication or taking the
  // remainder of division.
  double term();

  // The result of calculating the factorial.
  double factorialTerm();

  // Calculates the value in brackets and parentheses, calculates the result of
  // unary + and -, and returns the value of a numeric literal or variable.
  double primary();

  // Calculates the expression in brackets and parentheses.
  double handleParentesis(TokenKind closeParentesisKind);

  // Rreturns the value of the variable with name varName.
  double getVarValue(const std::string& varName);

  // Forces token stream to ignore all characters until the result output
  // character is encountered.
  // Used when eliminating expression input errors.
  void cleanUpMess();

  // Stores the variable with name varName and value varValue in the pVarTable.
  void setVarValue(const std::string& varName, double varValue);

  // Returns true if the variable with name varName is stored in the pVarTable.
  bool isVarDeclared(const std::string& varName);

 public:
  Calculator();

  // Starts the calculation process.
  void calculate();

  void defineVar(const std::string& varName, double varValue);

  void redefineVar(const std::string& varName, double varValue);
};