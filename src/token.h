#pragma once
#include <string>

enum class TokenType {
  INT, 
  RETURN,
  INDENTIFIER,
  NUMBER,

  LPAREN,
  RPAREN,
  LBRACE,
  RBRACE,
  SEMICOLON,

  END_OF_FILE
};

struct Token {
  TokenType type;
  std::string lexeme;
};
