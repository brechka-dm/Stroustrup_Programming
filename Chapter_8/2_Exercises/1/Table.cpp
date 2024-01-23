#include "Table.h"

#include "Error.h"

bool Table::isDeclared(const std::string& varname) const {
  return pVarTable.find(varname) != pVarTable.end();
}

void Table::define(const std::string& varname, double value, bool isConst) {
  if (isDeclared(varname))
    error("Variable \"" + varname + "\" is declared twice");
  pVarTable[varname] = Variable(varname, value, isConst);
}

void Table::redefine(const std::string& varname, double value) {
  if (!isDeclared(varname))
    error("Variable \"" + varname + "\" is not declared");
  pVarTable[varname].setValue(value);
}

void Table::set(const std::string& varname, double value) {
  if (isDeclared(varname)) pVarTable[varname].setValue(value);
  error("set: \"" + varname + "\" variable is undefined");
}

double Table::get(const std::string& varname) const {
  if (!isDeclared(varname))
    error("get: \"" + varname + "\" variable is undefined");
  return pVarTable.at(varname).getValue();
}