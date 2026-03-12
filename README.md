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

Currently implemented:

* project structure
* token definitions
* compiler skeleton
* test input

Next step:

* implement the **lexer** (tokenizer)

---

## Project Structure

```
mini-compiler
├── include
│   └── token.h
├── src
│   ├── lexer.cpp
│   └── main.cpp
├── tests
│   └── test.c
└── Makefile
```

---

## Build

```
make
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

