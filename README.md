# c-minus-compiler

A comprehensive **C-like language compiler**

A comprehensive **C-like language compiler** that translates custom source code into **MIPS assembly**. Built with Flex, Bison, and C, this educational compiler demonstrates core compiler concepts including lexical analysis, parsing, AST construction, and code generation.

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Language: C](https://img.shields.io/badge/Language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Build: Make](https://img.shields.io/badge/Build-Make-brightgreen.svg)](https://www.gnu.org/software/make/)

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Quick Start](#quick-start)
- [Installation](#installation)
- [Usage](#usage)
- [Language Features](#features)
- [Architecture](#architecture)
- [Examples](#examples)
- [Testing](#testing)
- [Contributing](#contributing)
- [License](#license)

## Overview

This compiler implements a subset of C-like syntax and compiles it into executable MIPS assembly code. It's ideal for learning compiler design, studying intermediate code generation, and understanding how source code is transformed into machine instructions.

**Key Capabilities:**
- 🔤 Lexical analysis with Flex
- 🌳 Abstract Syntax Tree (AST) construction
- 🏷️ Symbol table with scope management
- 📝 Three-Address Code (TAC) generation
- ⚙️ MIPS assembly code generation
- 🚀 Performance benchmarking

---

## Features

### Data Types
- **int** - Integer variables
- **char** - Character variables  
- **string** - String literals

### Variables
- Simple variable declarations
- Variable initialization
- Automatic `var_` prefix for MIPS compatibility (prevents conflicts with MIPS reserved words)

### Arrays
- **1D Arrays**: `int arr[10];`
- **2D Arrays**: `int matrix[5][5];`
- Array initialization: `int arr[3] = {1, 2, 3};`
- Array access: `arr[i]`, `matrix[i][j]`

### Operators

#### Arithmetic Operators
- Addition: `+`
- Subtraction: `-`
- Multiplication: `*`
- Division: `/`
- Modulo: `%`

#### Compound Assignment Operators
- `+=` (add and assign)
- `-=` (subtract and assign)
- `*=` (multiply and assign)
- `/=` (divide and assign)
- `%=` (modulo and assign)

#### Unary Operators
- `++` (increment: both pre and post)
- `--` (decrement: both pre and post)

#### Comparison Operators
- Equal: `==`
- Not equal: `!=`
- Less than: `<`
- Less than or equal: `<=`
- Greater than: `>`
- Greater than or equal: `>=`

#### Logical Operators
- AND: `&&`
- OR: `||`
- NOT: `!`
- XOR: `^`

### Control Flow

#### Conditional Statements
- **if** statements
- **if-else** statements
- **if-elseif-else** chains
- Nested conditions with logical operators

#### Loop Statements
- **for loops**: `for (init; condition; update) { body }`
  - Supports variable declarations in initialization
  - Supports increment/decrement operators in update
- **while loops**: `while (condition) { body }`
- **do-while loops**: `do { body } while (condition);`
- Nested loops supported

### Functions
- **Function Definitions**: Define reusable code blocks
- **Parameters**: Pass values to functions
- **Return Values**: Functions can return values
- **Recursion**: Full support for recursive function calls
- **Function Calls**: Call functions from anywhere in your code

### Built-in Functions
- `write(expression)` - Output values to console

### Basic Variables and Arithmetic
```c
int x;
x = 10;
int y = 20;
int sum = x + y;
write(sum);
```

### Arrays
```c
int arr[5] = {10, 20, 30, 40, 50};
int i;
for (i = 0; i < 5; i++) {
    write(arr[i]);
}
```

### Functions and Recursion
```c
function int factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

int result = factorial(5);
write(result);  // Output: 120
```

### Nested Loops and 2D Arrays
```c
int matrix[3][3];
int i, j;

for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
        matrix[i][j] = i * 3 + j;
        write(matrix[i][j]);
    }
}
```

## Testing

### Included Test Files

| File | Purpose |
|------|---------|
| `test.c` | Basic feature testing |
| `test_functions.c` | Function definitions and calls |
| `test_recursive.c` | 6 recursive function examples (Factorial, Fibonacci, etc.) |
| `test_advanced_recursion.c` | Advanced recursion (Ackermann, Tower of Hanoi, etc.) |
| `test_errors.c` | Error handling tests |
| `comprehensive_test.cm` | Comprehensive feature test suite |

### Running Tests
```bash
make test
```

## Architecture

**See [ARCHITECTURE.md](ARCHITECTURE.md) for detailed technical documentation.**

### High-Level Components

| Component | Files | Purpose |
|-----------|-------|---------|
| **Lexer** | `lexer.l` | Tokenizes source code |
| **Parser** | `parser.y` | Builds Abstract Syntax Tree |
| **AST** | `AST.c/h` | Tree representation with memory pooling |
| **Symbol Table** | `symtab.c/h` | Variable and scope management |
| **Code Generator** | `codegen.c/h` | MIPS assembly generation |
| **TAC** | `tac.c/h` | Three-address code IR |
| **String Pool** | `stringpool.c/h` | Efficient string storage |
| **Error Handler** | `error.c/h` | Error reporting and diagnostics |

### Memory Management
- 🎯 Custom AST node pooling (reduces malloc overhead)
- 📝 String interning via hash table (reduces memory usage)
- 🔍 Hash-based symbol table (O(1) lookup)

### Optimizations
- String deduplication
- Efficient register allocation
- Minimal stack usage

## Language Syntax Reference

### Data Types
- `int` - 32-bit integer
- `char` - Single character
- `string` - String literals

### Operators
```c
// Arithmetic
+, -, *, /, %

// Comparison
==, !=, <, <=, >, >=

// Logical
&&, ||, !, ^

// Unary
++, --

// Assignment
=, +=, -=, *=, /=, %=
```

### Control Flow
```c
if (condition) { }
else if (condition) { }
else { }

for (init; cond; update) { }
while (condition) { }
do { } while (condition);
```

### Functions
```c
function <type> <name>(<params>) {
    return <value>;
}
```

## Known Limitations

- ❌ No pointers
- ❌ No structs or user-defined types
- ❌ Integer arithmetic only (no floating point)
- ❌ Limited standard library (only `write()`)
- ❌ No break/continue statements

## Future Enhancements

- [ ] Break and continue statements
- [ ] Switch-case statements
- [ ] Additional built-in functions
- [ ] Enhanced type checking
- [ ] Optimization passes
- [ ] Better error messages with line numbers

## Contributing

Contributions are welcome! Please see [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines.

## Authors

- **Andru Tjalas**
- **Tatum Hansen**

## License

This project is licensed under the MIT License. See [LICENSE](LICENSE) for details.

---

## Support

For issues, questions, or suggestions, please open an issue on GitHub.

**Last Updated:** December 2025

## Quick Start

### Build and Run
```bash
# Clone and navigate to the project
cd c-minus-compiler

# Build the compiler
make

# Compile a source file to MIPS assembly
./Compiler examples/hello.c output.s

# Run the generated MIPS code
spim -file output.s
```

## Installation

**See [INSTALLATION.md](INSTALLATION.md) for detailed setup instructions.**

### Prerequisites
- **GCC** - C compiler (v7.0+)
- **Flex** - Lexer generator (v2.6+)
- **Bison** - Parser generator (v3.0+)
- **SPIM** - MIPS simulator (for executing output)

### Platform Support
- ✅ Linux
- ✅ macOS
- ✅ Windows (MinGW/Cygwin)

### Building
```bash
make           # Build the compiler
make clean     # Remove build artifacts
make test      # Run test suite
```

## Usage

### Command-line Interface
```bash
./Compiler <source_file> <output_file>
```

**Parameters:**
- `source_file` - Input .c file with custom language syntax
- `output_file` - Output .s MIPS assembly file

### Example
```bash
./Compiler program.c output.s
spim -file output.s
```

### Compilation Pipeline
```
Source Code (.c)
    ↓
[Lexer] (Flex)
    ↓
Token Stream
    ↓
[Parser] (Bison)
    ↓
Abstract Syntax Tree (AST)
    ↓
[Semantic Analysis] (Symbol Table)
    ↓
[Intermediate Code Generation] (TAC)
    ↓
[Code Generator]
    ↓
MIPS Assembly (.s)
```

## Test Files Included

- `test.c` - Basic feature testing
- `test_functions.c` - Function definitions and calls including factorial
- `test_recursive.c` - **6 recursive function examples:**
  - Factorial
  - Fibonacci
  - Sum to N
  - Power (exponentiation)
  - GCD (Euclidean algorithm)
  - Countdown
- `test_advanced_recursion.c` - Advanced recursive examples:
  - Ackermann function
  - Tower of Hanoi
  - Digital root
- `test_errors.c` - Error handling tests
- `test_performance.sh` - Performance benchmarking

## Recursive Functions

**Your compiler fully supports recursive functions!** See `RECURSION_GUIDE.md` for a detailed explanation.

### Quick Recursive Example
```c
function int factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    int prev;
    prev = n - 1;
    int prevFact;
    prevFact = factorial(prev);  // Recursive call
    return n * prevFact;
}

int result;
result = factorial(5);  // Returns 120
write(result);
```

### How Recursion Works
- Each function call gets its own stack frame
- Return addresses are properly saved and restored
- Parameters and local variables are independent per call
- Base cases prevent infinite recursion

**See `RECURSION_GUIDE.md` for complete documentation!**

## Compiler Architecture

### Components
- **Lexer** (`lexer.l`) - Tokenizes source code
- **Parser** (`parser.y`) - Builds Abstract Syntax Tree (AST)
- **AST** (`AST.c/h`) - Tree representation with memory pooling
- **Symbol Table** (`symtab.c/h`) - Variable and scope management
- **Code Generator** (`codegen.c/h`) - MIPS assembly generation
- **TAC** (`tac.c/h`) - Three-address code intermediate representation
- **String Pool** (`stringpool.c/h`) - Efficient string storage

### Memory Management
- Custom memory pooling for AST nodes
- Efficient string interning via string pool
- Hash-based symbol table with O(1) lookup

### Optimizations
- String interning reduces memory usage
- Memory pool allocation reduces malloc overhead
- Efficient MIPS register usage

## Language Syntax Summary

```c
// Variable declarations
int x;
char c;
string s = "hello";

// Arrays
int arr[10];
int matrix[5][5] = {1, 2, 3, 4, 5};

// Arithmetic
x = (a + b) * c / d % e;

// Compound operators
x += 10;
i++;
--j;

// Control flow
if (condition) {
    // statements
} elseif (other_condition) {
    // statements
} else {
    // statements
}

for (int i = 0; i < 10; i++) {
    // statements
}

while (condition) {
    // statements
}

do {
    // statements
} while (condition);

// Output
write(expression);
```

## Known Limitations

- No pointers
- No structs or user-defined types
- Integer arithmetic only (no floating point)
- Limited standard library (only write function)

## Future Enhancements

- Break and continue statements
- Switch-case statements
- Additional built-in functions
- Type checking improvements
- Code optimization passes

## Contributors

- Andru Tjalas
- Tatum Hansen

---


