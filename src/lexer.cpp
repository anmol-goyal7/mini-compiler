#include <string>
#include <cctype>

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


    
    
};
