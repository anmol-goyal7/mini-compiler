#include "codegen.h"

#include <sstream>

std::string CodeGen::generate(const Program& program) const {
  std::ostringstream out;
  const Function& fn = program.function;

  out << "    .text\n";
  out << "    .globl " << fn.name << "\n";
  out << fn.name << ":\n";
  out << "    movl $" << fn.body.expression.value << ", %eax\n";
  out << "    ret\n";
  // Tells the linker this object does not need an executable stack.
  out << "    .section .note.GNU-stack,\"\",@progbits\n";

  return out.str();
}
