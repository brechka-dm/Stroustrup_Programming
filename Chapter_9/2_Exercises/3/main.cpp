#include <iostream>

#include "NamePairs.h"

/*
 * This program is a solution of Exercise 3 from Chapter 9.
 * "Replace the Name_pair::print() function with a (global) operator
 * operator<< and define the operators == and != for objects of class Name_pair.
 */

int main() {
  std::cout << "Obj1: " << std::endl;
  NamePairs obj;
  obj.readNames();
  obj.readAges();
  std::cout << obj;
  std::cout << "Obj2: " << std::endl;
  NamePairs obj2;
  obj2.readNames();
  obj2.readAges();
  std::cout << obj2;

  std::cout << "Obj1 != Obj2 " << std::boolalpha << (obj != obj2);
}