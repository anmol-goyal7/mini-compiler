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
