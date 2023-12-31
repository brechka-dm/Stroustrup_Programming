#pragma once

#include "TokenStream.h"

#include <string>
#include <unordered_map>

class Grammar {
std::unordered_map<std::string, double> varTable;
TokenStream pTokenStream;

double getValue(const std::string& n);
double factorial(double arg);
double expression();
double primary();
double handleParentesis(char closeParentesisType);
double factorialTerm();
double term();
void cleanUpMess();
double getVarValue(const std::string& varName);
void setVarValue(const std::string& varName, double varValue);
bool isVarDeclared(const std::string& varName);
double defineVar(const std::string& varName, double varValue);

public:
Grammar();
};