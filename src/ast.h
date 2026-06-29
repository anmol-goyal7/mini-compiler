#pragma once
#include <string>

struct NumberLiteral {
    int value;
};

struct ReturnStatement {
    NumberLiteral expression;
};

struct Function {
    std::string name;
    ReturnStatement body;
};

struct Program {
    Function function;
};
