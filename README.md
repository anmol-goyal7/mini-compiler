# Mini C Compiler

A small C compiler written in **C++** built from scratch to understand how compilers work internally.

The goal of this project is to gradually build a working compiler that translates a subset of C into **x86-64 assembly**.

This project focuses on learning:

* lexical analysis
* parsing
* abstract syntax trees
* code generation
* compiler architecture

---

## Project Goal

Implement a minimal C compiler step by step.

Pipeline:

```
C source code
      ↓
Lexer (tokenizer)
      ↓
Parser
      ↓
Abstract Syntax Tree (AST)
      ↓
Code Generator
      ↓
x86-64 Assembly
      ↓
Executable
```

Example program:

```c
int main() {
    return 42;
}
```

Target output (assembly):

```asm
.global main
main:
    mov $42, %rax
    ret
```

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
* **Test input** (`tests/test.c`) — simple `return 42` program

### In Progress

* **Main driver** (`src/main.cpp`) — entry point to wire lexer to file input and print tokens
* **Makefile** — build configuration

### Not Yet Started

* Parser (recursive descent)
* AST node definitions
* Code generator (x86-64 assembly output)

---

## Project Structure

```
mini-compiler
├── src
│   ├── lexer.cpp      # Tokenizer implementation
│   ├── token.h        # Token type definitions
│   └── main.cpp       # Compiler entry point (WIP)
├── tests
│   └── test.c         # Test C program
├── Makefile           # Build configuration (WIP)
└── README.md
```

---

## Build

```
make
```

*(Makefile not yet configured)*

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
