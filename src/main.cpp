#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "codegen.h"
#include "error.h"
#include "lexer.h"
#include "parser.h"

std::string readFile(const std::string& path) {
  std::ifstream file(path);
  if (!file) {
    throw std::runtime_error("could not open file: " + path);
  }
  std::stringstream ss;
  ss << file.rdbuf();
  return ss.str();
}

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "usage: " << argv[0] << " <input.c>\n";
    return 1;
  }
  try {
    // 1. read the source file
    std::string source = readFile(argv[1]);

    // 2. lex: source -> tokens
    Lexer lexer(source);
    std::vector<Token> tokens = lexer.tokenize();

    // 3. parse: tokens -> AST
    Parser parser(tokens);
    Program program = parser.parseProgram();

    // 4. codegen: AST -> assembly, written to stdout
    CodeGen codegen;
    std::cout << codegen.generate(program);
  } catch (const CompileError& e) {
    std::cerr << argv[1] << ":" << e.what() << "\n";
    return 1;
  } catch (const std::exception& e) {
    std::cerr << "mycc: " << e.what() << "\n";
    return 1;
  }
  return 0;
}
