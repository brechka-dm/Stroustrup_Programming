#pragma once

#include <string>
#include <vector>

class NamePairs {
  std::vector<std::string> pNames{};
  std::vector<double> pAges{};

 public:
  class InvalidInput {};
  void readNames();
  void readAges();
  void sort();
  std::vector<std::string> getNames() const { return pNames; }
  std::vector<double> getAges() const { return pAges; }

  bool operator==(const NamePairs& other) const;
  bool operator!=(const NamePairs& other) const;
};

std::ostream& operator<<(std::ostream& stream, const NamePairs& object);