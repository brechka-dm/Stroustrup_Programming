#pragma once

#include "TokenStream.h"

/*
 * This class is responsible for logic grammar recognizing.
 *
 * This file provides the definition of the class interface, the implementation
 * is given in the file LogicGrammarRecognizer.cpp (see Chapter 9.2).
 */
class LogicGrammarRecognizer {
  // TokenStream is described in TokenStream.h
  TokenStream pTokenStream;

  bool primaryExpression();
  bool expression();
  bool term();

 public:
  LogicGrammarRecognizer();

  bool recognize(const std::string& str);
};