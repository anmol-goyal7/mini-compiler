#pragma once
#include <string>
#include <vector>

#include "ast.h"
#include "token.h"

// Recursive descent parser for:
//
//   program   -> function EOF
//   function  -> "int" IDENTIFIER "(" ")" "{" statement "}"
//   statement -> "return" NUMBER ";"
class Parser {
  public:
    explicit Parser(const std::vector<Token>& toks);

    Program parseProgram();

  private:
    std::vector<Token> tokens;
    size_t pos = 0;

    const Token& peek() const;
    Token advance();
    Token expect(TokenType type, const std::string& what);

    Function parseFunction();
    ReturnStatement parseReturn();
};
