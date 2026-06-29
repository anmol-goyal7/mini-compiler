#include <string>
#include <sstream>
#include "ast.h"

class CodeGen {
    public:
        std::string generate(const Program& program) {
            std::ostringstream out;
            const Function& fn = program.function;

            out << ".global " << fn.name << "\n";
            out << fn.name << ":\n";
            out << "    mov $" << fn.body.expression.value << ", %rax\n";
            out << "    ret\n";

            return out.str();
    }
};
        
