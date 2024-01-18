#pragma once

#include <string>
#include <unordered_map>

#include "Variable.h"

/*
 * Supports working with a table of variables.
 * Added as per exercise 9.
 */
class Table {
  std::unordered_map<std::string, Variable> pVarTable;
  bool isDeclared(const std::string& varname) const;

 public:
  void define(const std::string& varname, double value, bool isConst);
  void redefine(const std::string& varname, double value);
  void set(const std::string& varname, double value);
  double get(const std::string& varname) const;
};