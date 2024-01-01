#include "Calculator.h"

#include <iostream>

using std::cout;
using std::endl;

namespace {
const char prompt = '>';
}

void Calculator::calculate() { pGrammar.inputText(); }
void Calculator::defineVar(const std::string& varName, double varValue) {
  pGrammar.defineVar(varName, varValue);
}