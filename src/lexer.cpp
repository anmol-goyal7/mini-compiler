#include <string>

class Lexer {
  private:
    std::string source;
    size_t pos;

  public:
    Lexer(const std::string& src) : source(src), pos(0) {}
}
