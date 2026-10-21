#pragma once
#include <stdexcept>
#include <string>

// An error in the input program, reported as "line:column: message".
class CompileError : public std::runtime_error {
  public:
    CompileError(int line, int column, const std::string& message)
        : std::runtime_error(std::to_string(line) + ":" + std::to_string(column) + ": " + message) {}
};
