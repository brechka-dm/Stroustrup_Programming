#pragma once

#include <iostream>

/*
 * Handles an error in the program.
 * Displays "false" (because the string is not recognized) and terminates the
 * program.
 */
inline void error() {
  std::cout << std::boolalpha << false << std::endl;

  // Used to terminate the program.
  exit(1);
}