#pragma once

/*
 * Contains available token types. 
 */
enum class TokenType {
  Literal,
  OpenParenthesis,
  CloseParenthesis,
  EndOfString,
  Inversion,
  Extension,
  Conjunction,
  Disjunction,
  Invalid
};