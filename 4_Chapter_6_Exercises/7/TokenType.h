#pragma once

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