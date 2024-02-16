#pragma once

#include <string>
#include <vector>

class NamePairs {
  std::vector<std::string> pNames;
  std::vector<double> pAges;

 public:
  // The exception class.
  class InvalidInput {};

  // Reads names as a string line until "end" is entered. The results stored in
  // pNames.
  void readNames();

  // Prompts to enter an age for each item in the pNames. Throws InvalidInput in
  // case of incorrect input.
  void readAges();
  void sort();
  void print() const;
};