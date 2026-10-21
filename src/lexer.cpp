#include "lexer.h"

#include <cctype>

#include "error.h"

namespace {
bool isIdentChar(char c) {
  return std::isalnum(static_cast<unsigned char>(c)) || c == '_';
}
bool isDigit(char c) {
  return std::isdigit(static_cast<unsigned char>(c));
}
} // namespace

Lexer::Lexer(const std::string& src) : source(src) {}

bool Lexer::isAtEnd() const {
  return pos >= source.length();
}

char Lexer::peek() const {
  return isAtEnd() ? '\0' : source[pos];
}

char Lexer::peekNext() const {
  return pos + 1 >= source.length() ? '\0' : source[pos + 1];
}

void Lexer::advance() {
  if (isAtEnd()) return;
  if (source[pos] == '\n') {
    line++;
    column = 1;
  } else {
    column++;
  }
  pos++;
}

void Lexer::skipWhitespaceAndComments() {
  while (!isAtEnd()) {
    char c = peek();
    if (std::isspace(static_cast<unsigned char>(c))) {
      advance();
    } else if (c == '/' && peekNext() == '/') {
      while (!isAtEnd() && peek() != '\n') advance();
    } else if (c == '/' && peekNext() == '*') {
      int startLine = line, startColumn = column;
      advance();
      advance();
      while (!(peek() == '*' && peekNext() == '/')) {
        if (isAtEnd()) throw CompileError(startLine, startColumn, "unterminated comment");
        advance();
      }
      advance();
      advance();
    } else {
      return;
    }
  }
}

std::string Lexer::readWhile(bool (*pred)(char)) {
  size_t start = pos;
  while (!isAtEnd() && pred(peek())) advance();
  return source.substr(start, pos - start);
}

Token Lexer::nextToken() {
  skipWhitespaceAndComments();

  int tokLine = line, tokColumn = column;
  auto make = [&](TokenType type, std::string text) {
    return Token{type, std::move(text), tokLine, tokColumn};
  };

  if (isAtEnd()) return make(TokenType::END_OF_FILE, "");

  char c = peek();

  if (std::isalpha(static_cast<unsigned char>(c)) || c == '_') {
    std::string text = readWhile(isIdentChar);
    if (text == "int") return make(TokenType::INT, text);
    if (text == "return") return make(TokenType::RETURN, text);
    return make(TokenType::IDENTIFIER, text);
  }

  if (isDigit(c)) {
    std::string number = readWhile(isDigit);
    if (isIdentChar(peek())) {
      throw CompileError(tokLine, tokColumn, "invalid number '" + number + peek() + "...'");
    }
    return make(TokenType::NUMBER, number);
  }

  advance();
  switch (c) {
    case '(': return make(TokenType::LPAREN, "(");
    case ')': return make(TokenType::RPAREN, ")");
    case '{': return make(TokenType::LBRACE, "{");
    case '}': return make(TokenType::RBRACE, "}");
    case ';': return make(TokenType::SEMICOLON, ";");
  }

  // Anything else is outside the supported subset. Failing here matters:
  // treating it as end-of-file would silently drop the rest of the program.
  throw CompileError(tokLine, tokColumn, std::string("unexpected character '") + c + "'");
}

std::vector<Token> Lexer::tokenize() {
  std::vector<Token> tokens;
  do {
    tokens.push_back(nextToken());
  } while (tokens.back().type != TokenType::END_OF_FILE);
  return tokens;
}
