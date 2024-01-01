#pragma once

#include <string>
#include <unordered_map>

#include "Grammar.h"

class Calculator {
  std::unordered_map<std::string, double> pVarTable;
  Grammar pGrammar;

 public:
  void calculate();
  void defineVar(const std::string& varName, double varValue);
};