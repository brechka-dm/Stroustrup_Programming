#pragma once

#include <iostream>

inline void error() {
  std::cout << std::boolalpha << false << std::endl;
  exit(1);
}