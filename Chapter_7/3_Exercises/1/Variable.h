#pragma once

#include <string>

/*
 * Stores variable name and value.
 */
class Variable {
  std::string pName;
  double pValue{};

  // If true, the value  cannot be changed.
  bool pIsConst{false};

 public:
  Variable();
  Variable(const std::string& name, double value, bool isConst = false);
  // Throws exception if pIsConst is true.
  void setValue(double value);
  double getValue() const { return pValue; }
  const std::string& getName() const { return pName; }
  bool isConst() const { return pIsConst; }
};