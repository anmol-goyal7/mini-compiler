#include <vector>
#include <stdexcept>
#include "token.h"
#include "ast.h"

class Parser {
    private:
        std::vector<Token> tokens;
        size_t pos;

        
        Token peek() {
            return tokens[pos];
    }

        Token advance() {
            return tokens[pos++];
    }

        Token expect(TokenType type, const std::string& what) {
            if (peek().type != type) {
                throw std::runtime_error("Parse error: expected " + what +
                                         " but got '" + peek().lexeme + "'");
      }
      return advance();
    }

    public:

        Parser(const std::vector<Token>& toks) : tokens(toks), pos(0) {}

        Program parseProgram() {

            Program program;
            program.function = parseFunction();
            expect(TokenType::END_OF_FILE, "end of file");
            return program;
    }

        Function parseFunction() {
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

        ReturnStatement parseReturn() {
            expect(TokenType::RETURN, "'return'");
            Token num = expect(TokenType::NUMBER, "a number");
            expect(TokenType::SEMICOLON, "';'");

            ReturnStatement stmt;
            stmt.expression.value = std::stoi(num.lexeme);
            return stmt;
    }
};

