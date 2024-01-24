#include "Print.h"

#include <iostream>

void print(const std::string& msg, const std::vector<int>& vector) {
  std::cout << msg << ": ";
  for (auto it = vector.begin(); it != vector.end(); ++it)
    std::cout << *it << " ";
  std::cout << std::endl;
}