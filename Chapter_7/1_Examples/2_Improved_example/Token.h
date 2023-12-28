#pragma once

#include <string>

class Token {
  std::string pName;
  double pValue{0.0};
  char pKind{0};

 public:
  Token(char ch) : pKind(ch), pValue(0.0) {}
  Token(char ch, double val) : pKind(ch), pValue(val) {}
  Token(char ch, std::string n) : pKind(ch), pName(n) {}

  char getKind() const { return pKind; }
  double getValue() const { return pValue; }
  const std::string& getName() const { return pName; }
};