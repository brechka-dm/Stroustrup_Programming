#pragma once

#include "TokenStream.h"

/*
 * This class is responsible for logic grammar recognizing.
 *
 * This file provides the definition of the class interface, the implementation
 * is given in the file LogicGrammarRecognizer.cpp (see Chapter 9.2).
 *
 * Grammar description:
 * Primary expression:
 *  Literal
 *  (Token)
 * Expression:
 *  Primary expression & Primary expression
 *  Primary expression ^ Primary expression
 * Term:
 *  ~Expression
 *  !Expression
 *  Expression
 */
class LogicGrammarRecognizer {
  // TokenStream is described in TokenStream.h
  TokenStream pTokenStream;

  bool primaryExpression();
  bool expression();
  bool term();

 public:
  LogicGrammarRecognizer();

  // Returns true or false dependin on whether the str is an logical expression
  // or not.
  bool recognize(const std::string& str);
};