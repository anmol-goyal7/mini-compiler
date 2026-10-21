#pragma once
#include <string>

#include "ast.h"

class CodeGen {
  public:
    // Emits GNU-assembler x86-64 (AT&T syntax) for Linux.
    std::string generate(const Program& program) const;
};
