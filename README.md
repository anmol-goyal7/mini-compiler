# Mini C Compiler

A small C compiler written in C++, built from scratch to translate a subset of C into x86-64 assembly.

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

## Current Status

### Implemented

- **Token definitions** (`src/token.h`) -- enum of token types (`int`, `return`, identifiers, numbers, parens, braces, semicolons) and `Token` struct
- **Lexer** (`src/lexer.cpp`) -- tokenizer with whitespace skipping, identifier/keyword recognition (`int`, `return`), number literals, symbol recognition (`(`, `)`, `{`, `}`, `;`), and lookahead via `peek`/`peekNext`/`advance`
- **Test input** (`tests/test.c`) -- minimal `return 42` program

### Not Yet Started

- Parser (recursive descent)
- AST node definitions
- Code generator (x86-64 assembly output)
- Main driver to wire everything together

## Project Structure

```
mini-compiler
├── src
│   ├── lexer.cpp      # Tokenizer
│   ├── token.h        # Token type definitions
│   └── main.cpp       # Entry point (WIP)
├── tests
│   └── test.c         # Test C program
├── Makefile
└── README.md
```

## Target

Given:

```c
int main() {
    return 42;
}
```

The compiler should produce:

```asm
.global main
main:
    mov $42, %rax
    ret
```
<<<<<<< HEAD
=======

---

## Current Status

### Completed

* **Project structure** — source, test, and build directories
* **Token definitions** (`src/token.h`) — enum of token types and `Token` struct
* **Lexer** (`src/lexer.cpp`) — fully implemented tokenizer with:
  * whitespace skipping
  * identifier and keyword recognition (`int`, `return`)
  * number literal tokenization
  * symbol recognition (`(`, `)`, `{`, `}`, `;`)
  * `peek`, `peekNext`, and `advance` for character scanning
* **Parser** (`src/parser.cpp`) — recursive descent parser that produces an AST
* **AST** (`src/ast.h`) — node definitions for `Program`, `Function`, `ReturnStatement`, `NumberLiteral`
* **Code Generator** (`src/codegen.cpp`) — emits x86-64 assembly from the AST
* **Main driver** (`src/main.cpp`) — entry point that wires lexer, parser, and codegen together
* **Makefile** — build and test configuration
* **Test input** (`tests/test.c`) — simple `return 42` program

---

## Project Structure

```
mini-compiler
├── src
│   ├── token.h        # Token type definitions
│   ├── ast.h          # AST node definitions
│   ├── lexer.cpp      # Tokenizer implementation
│   ├── parser.cpp     # Recursive descent parser
│   ├── codegen.cpp    # x86-64 assembly code generator
│   └── main.cpp       # Compiler entry point
├── tests
│   └── test.c         # Test C program
├── Makefile           # Build and test configuration
└── README.md
```

---

## Build

```
make
```

To compile and run the test program:

```
make test
```

---

## Run

```
./mycc tests/test.c
```

---

## Learning Objectives

This project is meant to explore:

* how programming languages are implemented
* how compilers transform code step by step
* low level code generation
* systems programming concepts

---

## Future Features

Planned compiler capabilities:

* integer expressions
* operator precedence
* variables
* stack frame management
* control flow (`if`, `while`)
* functions
* full assembly generation
>>>>>>> 523f4b1 (a working compiler)

