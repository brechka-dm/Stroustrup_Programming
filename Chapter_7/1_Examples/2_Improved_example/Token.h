#pragma once

#include <string>

template<typename T>
class Token {
  std::string pName;
  T pValue{};
  char pKind{0};

 public:
  Token(char ch) : pValue{}, pKind(ch) {}
  Token(char ch, double val) : pValue(val), pKind(ch) {}
  Token(char ch, std::string n) : pName(n), pValue{}, pKind(ch) {}

  char getKind() const { return pKind; }
  T getValue() const { return pValue; }
  const std::string& getName() const { return pName; }
};