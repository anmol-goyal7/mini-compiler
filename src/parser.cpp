#include "parser.h"

#include <climits>

#include "error.h"

Parser::Parser(const std::vector<Token>& toks) : tokens(toks) {}

const Token& Parser::peek() const {
  return tokens[pos];
}

Token Parser::advance() {
  Token tok = tokens[pos];
  if (tok.type != TokenType::END_OF_FILE) pos++;
  return tok;
}

Token Parser::expect(TokenType type, const std::string& what) {
  const Token& tok = peek();
  if (tok.type != type) {
    std::string got = tok.type == TokenType::END_OF_FILE ? "end of file" : "'" + tok.lexeme + "'";
    throw CompileError(tok.line, tok.column, "expected " + what + " but got " + got);
  }
  return advance();
}

Program Parser::parseProgram() {
  Program program;
  program.function = parseFunction();
  expect(TokenType::END_OF_FILE, "end of file");
  return program;
}

Function Parser::parseFunction() {
  expect(TokenType::INT, "'int'");
  Token name = expect(TokenType::IDENTIFIER, "function name");
  expect(TokenType::LPAREN, "'('");
  expect(TokenType::RPAREN, "')'");
  expect(TokenType::LBRACE, "'{'");

  Function fn;
  fn.name = name.lexeme;
  fn.body = parseReturn();

  expect(TokenType::RBRACE, "'}'");
  return fn;
}

ReturnStatement Parser::parseReturn() {
  expect(TokenType::RETURN, "'return'");
  Token num = expect(TokenType::NUMBER, "an integer literal");
  expect(TokenType::SEMICOLON, "';'");

  // The lexer only produces digit strings, so the only way stoll can fail
  // here is a literal too long for long long.
  long long value = 0;
  try {
    value = std::stoll(num.lexeme);
  } catch (const std::out_of_range&) {
    value = LLONG_MAX;
  }
  if (value > INT_MAX) {
    throw CompileError(num.line, num.column, "integer literal " + num.lexeme + " does not fit in int");
  }

  ReturnStatement stmt;
  stmt.expression.value = static_cast<int>(value);
  return stmt;
}
