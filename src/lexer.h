#pragma once
#include <string>
#include <vector>

#include "token.h"

class Lexer {
  public:
    explicit Lexer(const std::string& src);

    Token nextToken();

    // Lexes the whole source; the last token is always END_OF_FILE.
    std::vector<Token> tokenize();

  private:
    std::string source;
    size_t pos = 0;
    int line = 1;
    int column = 1;

    bool isAtEnd() const;
    char peek() const;
    char peekNext() const;
    void advance();
    void skipWhitespaceAndComments();
    std::string readWhile(bool (*pred)(char));
};
