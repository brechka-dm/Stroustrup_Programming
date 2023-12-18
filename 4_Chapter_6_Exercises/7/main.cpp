#include <iostream>
#include <string>

// Plug in our own header file. See Chapter 8.
#include "LogicGrammarRecognizer.h"

/*
 * This program is the solution to Exercise 7 of Chapter 6 of PROGRAMMING.
 * Principles and Practice Using C++. 2nd edition.
 *
 * The program allows you to recognize logical expressions containing variables
 * consisting of one small letter of the Latin alphabet and operation signs: ~,
 * !, & and ^.
 * The program takes as input a string containing a logical expression, and
 * outputs a string true if the string is recognized and false otherwise. 
 */

int main() {
  std::string str;
  getline(std::cin, str);

  // LogicGrammarRecognizer described in LogicGrammarRecognizer.h
  LogicGrammarRecognizer recognizer;

  std::cout << "Input expression: " << std::endl;

  // std::boolalpha is used to display result as true/false.
  std::cout << std::boolalpha << recognizer.recognize(str) << std::endl;
  return 0;
}