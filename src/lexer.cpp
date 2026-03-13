#include <string>
#include <cctype>
#include "token.h"

class Lexer {
  private:
    std::string source;
    size_t pos;

  public:
    Lexer(const std::string& src) : source(src), pos(0) {}

    bool isAtEnd() {
      return pos >= source.length();
    }

    char peek() {
      if (isAtEnd()) return '\0';
      return source[pos];
    }

    void advance() {
      if(!isAtEnd()) {
        pos++;
      }
    }
    char peekNext() {
      if (pos + 1 >= source.length()) return '\0';
      return source[pos +1];
    }
    
    void skipWhitespace() {
      while (!isAtEnd() && std::isspace(peek())) {
        advance();
      }
    }
    
    std::string readIdentifier() {
      size_t start = pos;

      while(!isAtEnd() && (std::isalnum(peek()) || peek() == '_')) {
        advance();
      }

      return source.substr(start, pos - start);
    }
    
    TokenType readIdentifierType(const std::string& text) {
      if (text == "int") return TokenType::INT;
      if (text == "return") return TokenType::RETURN;

      return TokenType::IDENTIFIER;
    }
    
    std::string readNumber() {
      size_t start = pos;

      while(!isAtEnd() && std::isdigit(peek())) {
        advance();
      }
      
      return source.substr(start, pos - start);
    }

    Token nextToken() {
      skipWhitespace();
      
      if (isAtEnd()) {
        return {TokenType::END_OF_FILE, ""};
      }

      char c = peek();
      
      if (std::isalpha(c) || c == '_') {
        std::string text = readIdentifier();
        TokenType type = readIdentifierType(text);
        return {type, text};
      }

      if (std::isdigit(c)) {
        std::string number = readNumber();
        return {TokenType::NUMBER, number};
      }

      switch (c) {
        case '(':
          advance();
          return {TokenType::LPAREN, "("};

        case ')':
          advance();
          return {TokenType::RPAREN, ")"};

        case '{':
          advance();
          return {TokenType::LBRACE, "{"};

        case '}':
          advance();
          return {TokenType::RBRACE, "}"};

        case ';':
          advance();
          return {TokenType::SEMICOLON, ";"};
      }

      advance();
      return {TokenType::END_OF_FILE, ""};
    }
};


