#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "token.h"
#include "lexer.cpp"
#include "parser.cpp"
#include "codegen.cpp"

std::string readFile(const std::string& path) {
    std::ifstream file(path);
    if (!file) {
        throw std::runtime_error("Could not open file: " + path);
    }
    std::stringstream ss;
        ss << file.rdbuf();
        return ss.str();
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input.c>\n";
        return 1;
}
    try {
        std::string source = readFile(argv[1]);

    // 2. lex: produce token stream
        Lexer lexer(source);
        std::vector<Token> tokens;
        Token tok;
        do {
            tok = lexer.nextToken();
            tokens.push_back(tok);
        } while (tok.type != TokenType::END_OF_FILE);

    // 3. parse: tokens -> AST
        Parser parser(tokens);
        Program program = parser.parseProgram();

    // 4. codegen: AST -> assembly
        CodeGen codegen;
        std::string assembly = codegen.generate(program);

    // 5. write assembly to stdout
        std::cout << assembly;
    }

        catch (const std::exception& e) {
        std::cerr << e.what() << "\n";
        return 1;
       }
    return 0;
}

