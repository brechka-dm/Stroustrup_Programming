#pragma once

#include <string>

class Variable {
  std::string pName;
  double pValue{};
  bool pIsConst{false};

 public:
  Variable();
  Variable(const std::string& name, double value, bool isConst = false);
  void setValue(double value);
  double getValue() const { return pValue; }
  const std::string& getName() const { return pName; }
  bool isConst() const { return pIsConst; }
};