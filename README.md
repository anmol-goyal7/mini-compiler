# Mini C Compiler

A small compiler written in C++ from scratch: lexer, recursive descent parser, AST and x86-64 code generator. It currently handles the smallest C program — `int main() { return N; }` — end to end, and the pipeline is the base for growing the language.

## Pipeline

```
C source code
      |
Lexer (tokenizer)
      |
Parser
      |
Abstract Syntax Tree (AST)
      |
Code Generator
      |
x86-64 Assembly
      |
Executable
```

## What it compiles today

Exactly one shape of program: a single function with no parameters whose body is
one `return` of a non-negative integer literal.

```
program   -> function EOF
function  -> "int" IDENTIFIER "(" ")" "{" statement "}"
statement -> "return" NUMBER ";"
```

`//` and `/* */` comments are skipped. Anything outside that grammar — operators,
negative numbers, variables, a second function — is rejected with a
`file:line:column` error rather than silently ignored:

```
$ ./mycc bad.c
bad.c:1:21: unexpected character '-'
```

The output is GNU assembler x86-64 (AT&T syntax) for Linux; the function's return
value goes in `%eax`, so `main` returning N makes the program exit with status N.

## Project Structure

```
mini-compiler
├── src
│   ├── token.h        # token types and the Token struct (with line/column)
│   ├── error.h        # CompileError: "line:column: message"
│   ├── lexer.h/.cpp   # source -> tokens; skips whitespace and comments
│   ├── ast.h          # Program, Function, ReturnStatement, NumberLiteral
│   ├── parser.h/.cpp  # recursive descent parser: tokens -> AST
│   ├── codegen.h/.cpp # AST -> x86-64 assembly
│   └── main.cpp       # driver: read file, lex, parse, generate
├── tests
│   ├── valid/         # NAME_N.c must compile and exit with status N
│   ├── invalid/       # must be rejected with a line:column error
│   └── run.sh
├── Makefile
└── README.md
```

## Build

```
make
```

To run the test suite (compiles each test program, links it with `cc`, and checks
the exit status or the error):

```
make test
```

## Run

```
./mycc tests/valid/return_42.c
```

This prints the generated assembly to stdout. To produce an executable:

```
./mycc tests/valid/return_42.c > out.s
cc out.s -o out
./out; echo $?     # exits with 42
```

## Target

Given:

```c
int main() {
    return 42;
}
```

The compiler produces:

```asm
    .text
    .globl main
main:
    movl $42, %eax
    ret
    .section .note.GNU-stack,"",@progbits
```

## Learning Objectives

This project explores:

- how programming languages are implemented
- how compilers transform code step by step
- low-level code generation
- systems programming concepts

## Future Features

Planned compiler capabilities:

- unary minus and integer expressions
- operator precedence
- variables
- stack frame management
- control flow (`if`, `while`)
- functions
- full assembly generation
