# CST-405 Compiler Project

A fully-featured compiler that translates a C-like language into MIPS assembly code.

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

### Built-in Functions
- `write(expression)` - Output values to console

## Example Programs

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

### Loops with Operators
```c
int count = 10;
while (count > 0) {
    write(count);
    count--;
}

for (int i = 0; i < 10; i++) {
    if (i % 2 == 0) {
        write(i);  // Print even numbers
    }
}
```

### Compound Operators
```c
int x = 10;
x += 5;   // x = 15
x *= 2;   // x = 30
x %= 7;   // x = 2
write(x);
```

### Nested Loops and 2D Arrays
```c
int matrix[3][3];
int i;
int j;

for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
        matrix[i][j] = i * 3 + j;
        write(matrix[i][j]);
    }
}
```

### Complex Conditions
```c
int a = 5;
int b = 10;

if (a < b && b > 0) {
    write(1);
} elseif (a == b || b < 0) {
    write(2);
} else {
    write(3);
}
```

## Compilation & Execution

### Prerequisites
- GCC compiler
- Flex (lexer generator)
- Bison (parser generator)
- SPIM (MIPS simulator)

### Running the Compiler

1. **Build the compiler:**
   ```bash
   make
   ```

2. **Compile your source file:**
   ```bash
   ./Compiler input.c output.s
   ```
   
   Replace `input.c` with your source file and `output.s` with desired output file name.

3. **Run the MIPS assembly in SPIM:**
   ```bash
   spim -file output.s
   ```

### Example Workflow
```bash
make
./Compiler test.c output.s
spim -file output.s
```

### Clean Build
```bash
make clean
make
```

## Test Files Included

- `simple_loop_test.c` - Basic loop examples
- `test_loops.c` - Comprehensive loop testing
- `test_operators.c` - Operator demonstrations

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

- No function definitions (only main)
- No pointers
- No structs or user-defined types
- Integer arithmetic only (no floating point)
- Limited standard library (only write function)

## Future Enhancements

- Function definitions and calls
- Break and continue statements
- Switch-case statements
- Additional built-in functions
- Type checking improvements
- Code optimization passes

## Contributors

CST-405 Compilers Course Project

---

*For issues or questions, please refer to the course materials or contact the instructor.*
