#pragma once

#include <string>
#include <vector>

class NamePairs {
  std::vector<std::string> pNames;
  std::vector<double> pAges;

 public:
  class InvalidInput{};

  void readNames();
  void readAges();
  void sort();
  void print() const;
};