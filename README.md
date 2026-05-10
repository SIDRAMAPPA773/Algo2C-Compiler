# Algo2C-Compiler

A mini compiler project that converts custom pseudocode/algorithms into executable C code using FLEX and BISON with a modern IDE-style frontend.

## Features

- Lexical Analysis using FLEX
- Syntax Analysis using BISON
- Semantic Analysis
- Dynamic C Code Generation
- Symbol Table Management
- Error Detection
- Modern IDE-style Frontend
- IF/ELSE Support
- FOR Loop Support
- WHILE Loop Support

## Tech Stack

**Frontend:**
- HTML
- CSS
- JavaScript

**Backend:**
- FLEX
- BISON
- C
- GCC

## Project Architecture

This project uses a **Hybrid MVC + Compiler Pipeline Architecture**.

- **Lexer (FLEX):** Scans the input pseudocode and generates tokens.
- **Parser (BISON):** Checks the tokens against grammar rules and builds an Abstract Syntax Tree (AST).
- **Semantic Analyzer:** Tracks variable declarations and types using a Symbol Table.
- **Code Generator:** Traverses the AST to output formatted, valid C code dynamically.

## Folder Structure

```text
Algo2C-Compiler/
├── backend/            # Compiler source files
│   ├── lexer/          # FLEX lexer rules
│   ├── parser/         # BISON grammar rules
│   ├── semantic/       # Symbol table management
│   ├── codegen/        # AST traversal and C generation
│   ├── models/         # AST and token definitions
│   ├── controller/     # AST factory functions
│   └── main.c          # Core entry point
├── frontend/           # Web IDE interface
│   ├── css/            # UI styles
│   ├── js/             # UI controllers and API logic
│   └── views/          # HTML templates
└── server.js           # Node.js backend bridge
```

## Installation Steps

Ensure you have the required compiler tools installed:

```bash
sudo apt update
sudo apt install flex bison gcc
```

## Compilation Commands

Navigate to the `backend/` directory to build the compiler executable:

```bash
flex lexer.l
bison -d parser.y
gcc lex.yy.c parser.tab.c -o compiler
```

To run the compiler directly via terminal:
```bash
./compiler < input.txt
```

## Sample Input

```text
START
READ a
READ b
sum = a + b
PRINT sum
END
```

## Sample Generated C Output

```c
#include <stdio.h>

int main() {

    int a, b, sum;

    scanf("%d", &a);
    scanf("%d", &b);

    sum = a + b;

    printf("%d\n", sum);

    return 0;
}
```

## Screenshots

- **Main UI:** *(Placeholder for Main UI screenshot)*
- **Token Table:** *(Placeholder for Token Table screenshot)*
- **Generated C Code:** *(Placeholder for Generated C Code screenshot)*
- **Error Console:** *(Placeholder for Error Console screenshot)*

## Future Improvements

- AST Visualization
- Function Support
- Array Support
- Parse Tree Visualization
