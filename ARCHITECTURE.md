# Architecture Documentation

## Overview

The c-minus-compiler follows a traditional multi-pass compiler architecture. Source code flows through distinct phases: lexical analysis, parsing, semantic analysis, intermediate code generation, and finally code generation.

```
┌─────────────────┐
│   Source Code   │
└────────┬────────┘
         │
    ┌────▼────┐
    │  Lexer  │  (lexer.l)
    │ (Flex)  │  Tokenization
    └────┬────┘
         │
    ┌────▼────────────┐
    │ Token Stream    │
    └────┬────────────┘
         │
    ┌────▼────┐
    │ Parser  │  (parser.y)
    │ (Bison) │  Syntax Analysis
    └────┬────┘
         │
    ┌────▼─────┐
    │    AST   │  (AST.c/h)
    │   Build  │  Abstract Syntax Tree
    └────┬─────┘
         │
    ┌────▼──────────────┐
    │  Symbol Table     │  (symtab.c/h)
    │ Semantic Analysis │  Scope & Type Checking
    └────┬──────────────┘
         │
    ┌────▼────┐
    │   TAC    │  (tac.c/h)
    │ (IR Gen) │  Three-Address Code
    └────┬────┘
         │
    ┌────▼─────────┐
    │ Code Generator│ (codegen.c/h)
    │  MIPS Asm     │
    └────┬─────────┘
         │
    ┌────▼────────────┐
    │ MIPS Assembly   │
    │   (.s file)     │
    └─────────────────┘
```

---

## Phase 1: Lexical Analysis (Lexer)

**File:** `lexer.l` (Flex specification)

### Responsibilities
- Read source code character by character
- Recognize language tokens (keywords, identifiers, operators, literals)
- Track line numbers and positions for error reporting
- Skip whitespace and comments

### Key Tokens
| Token Type | Examples |
|------------|----------|
| Keywords | `int`, `char`, `string`, `if`, `while`, `for`, `function` |
| Identifiers | `x`, `myVar`, `calculate_value` |
| Operators | `+`, `-`, `*`, `/`, `=`, `==`, `&&` |
| Literals | `123`, `'a'`, `"hello"` |
| Delimiters | `{`, `}`, `(`, `)`, `;` |

### Output
- **Token Stream:** Sequence of tokens with values and types
- **Passed to:** Parser (parser.y)

---

## Phase 2: Parsing & AST Construction

**Files:** `parser.y` (Bison specification), `AST.c/h`

### Parsing (Bison)
**File:** `parser.y`

The parser implements a context-free grammar that matches the language syntax:
- **Productions:** Language grammar rules
- **Conflicts:** LR parser handles shift/reduce with standard precedence
- **Error Handling:** Reports syntax errors with messages

### Key Grammar Components
```
program        → declaration*
declaration    → variable_decl | function_decl
variable_decl  → type identifier [ '=' expression ] ';'
function_decl  → 'function' type identifier '(' params ')' block
block          → '{' statement* '}'
statement      → expr_stmt | if_stmt | loop | block
```

### AST (Abstract Syntax Tree)

**Files:** `AST.c/h`

Represents the program structure as a tree:

```
Program
├── VariableDecl (int x)
├── VariableDecl (int y = 10)
├── FunctionDecl (factorial)
│   ├── Param: int n
│   └── Block
│       ├── IfStatement
│       │   ├── Condition: n <= 1
│       │   ├── ThenBlock: return 1
│       │   └── ElseBlock: ...
│       └── ReturnStatement: n * factorial(n-1)
└── FunctionCall (factorial, [5])
```

### AST Node Types
```c
typedef enum {
    NODE_PROGRAM,
    NODE_DECL_VAR,
    NODE_DECL_FUNC,
    NODE_EXPR_BINARY,
    NODE_EXPR_UNARY,
    NODE_EXPR_CALL,
    NODE_EXPR_ARRAY_ACCESS,
    NODE_STMT_IF,
    NODE_STMT_WHILE,
    NODE_STMT_FOR,
    NODE_STMT_DO_WHILE,
    NODE_STMT_RETURN,
    NODE_STMT_WRITE,
    NODE_BLOCK,
    NODE_TYPE,
    NODE_LITERAL
} ASTNodeType;
```

### Memory Management
- **Pool Allocation:** Pre-allocates memory blocks for AST nodes
- **Benefit:** Reduces malloc overhead and fragmentation
- **Functions:**
  - `init_ast_memory()` - Initialize pool
  - `create_ast_node()` - Allocate from pool
  - `cleanup_ast_memory()` - Free all nodes

---

## Phase 3: Semantic Analysis (Symbol Table)

**Files:** `symtab.c/h`

### Responsibilities
- Track variable declarations and scope
- Verify function definitions
- Check for duplicate declarations
- Manage scope levels (global, function, block)

### Symbol Table Structure
```c
typedef struct {
    char* name;
    SymbolType type;        // VAR, FUNC, ARRAY, etc.
    int data_type;          // INT, CHAR, STRING
    int dimension[2];       // For arrays
    int scope_level;
    int offset;             // Stack offset
} Symbol;
```

### Scope Management
```
Global Scope (level 0)
├── int x
├── int y
└── function factorial (scope level 1)
    ├── int n
    ├── int prev
    └── Nested block (scope level 2)
        └── Variable declarations
```

### Key Functions
- `initSymTab()` - Initialize symbol table
- `enterScope()` - Enter a new scope
- `exitScope()` - Exit current scope
- `addSymbol()` - Add variable/function
- `lookupSymbol()` - Find symbol in current scope
- `lookupSymbolGlobal()` - Find in any scope

---

## Phase 4: Intermediate Code Generation (TAC)

**Files:** `tac.c/h`

### Three-Address Code (TAC)

Intermediate representation closer to machine code but language-independent:

```
// Original code
x = y + 5;

// TAC
t1 = 5
t2 = y + t1
x = t2
```

### TAC Instruction Types
```c
typedef enum {
    TAC_ASSIGN,           // x = y
    TAC_BINARY_OP,        // x = y OP z
    TAC_UNARY_OP,         // x = OP y
    TAC_ARRAY_ASSIGN,     // arr[i] = x
    TAC_ARRAY_ACCESS,     // x = arr[i]
    TAC_FUNC_CALL,        // x = func(args)
    TAC_RETURN,           // return x
    TAC_IF,               // if x goto L1
    TAC_GOTO,             // goto L1
    TAC_LABEL,            // L1:
    TAC_PARAM_PUSH,       // push x
    TAC_WRITE             // write x
} TACOpType;
```

### Benefits
- Simplifies code generation
- Enables optimization passes
- Easier to analyze and transform
- Language-independent representation

---

## Phase 5: Code Generation (MIPS Assembly)

**Files:** `codegen.c/h`

### Responsibilities
- Convert AST → MIPS assembly
- Manage register allocation
- Handle function prologue/epilogue
- Generate data segment for strings

### MIPS Architecture
- **32 registers** ($0-$31)
- **Register conventions:**
  - `$zero` - Always 0
  - `$sp` - Stack pointer
  - `$fp` - Frame pointer
  - `$ra` - Return address
  - `$a0-$a3` - Function arguments
  - `$v0-$v1` - Return values
  - `$t0-$t9` - Temporary (caller-saved)
  - `$s0-$s7` - Saved (callee-saved)

### Function Call Sequence
```
1. Caller: Push arguments ($a0-$a3)
2. Caller: Call function (jal)
3. Callee: Prologue (save $ra, $fp, allocate stack)
4. Callee: Execute function body
5. Callee: Place return value in $v0
6. Callee: Epilogue (restore $ra, $fp)
7. Callee: Return (jr $ra)
8. Caller: Retrieve return value from $v0
```

### Stack Layout
```
┌─────────────────┐  High addresses
│  Old $ra        │  (caller's return address)
├─────────────────┤
│  Old $fp        │
├─────────────────┤
│  Local vars     │  (current function)
├─────────────────┤
│  Temp storage   │
├─────────────────┤  $sp (Stack pointer)
│  (empty)        │
└─────────────────┘  Low addresses
```

### Code Generation Process
1. **Data Segment:** Emit strings and static data
2. **Text Segment:** Emit code
3. **For each function:**
   - Prologue (stack setup)
   - Function body
   - Epilogue (stack cleanup)
4. **System calls:** `syscall` for I/O

### MIPS Syscalls Used
| Service | Code | Purpose |
|---------|------|---------|
| print_int | 1 | Output integer |
| read_int | 5 | Input integer |
| exit | 10 | Exit program |

---

## Supporting Modules

### Error Handler (`error.c/h`)
- Collects compilation errors
- Reports line numbers and messages
- Prevents cascading errors

### String Pool (`stringpool.c/h`)
- Interns strings to save memory
- Hash-based lookup
- Returns unique pointers for identical strings

### Benchmark (`benchmark.c/h`)
- Measures compilation time
- Tracks performance of each phase
- Optional performance profiling

### Main (`main.c`)
- Entry point
- Orchestrates compilation phases
- Manages file I/O

---

## Data Flow Example

### Input Program
```c
function int add(int a, int b) {
    return a + b;
}

int x = 5;
int y = 3;
int result = add(x, y);
write(result);
```

### Lexer Output
```
FUNCTION INT ADD LPAREN INT A COMMA INT B RPAREN
LBRACE RETURN A PLUS B SEMICOLON RBRACE
INT X ASSIGN 5 SEMICOLON
...
```

### Parser Output (AST)
```
Program
├── FunctionDecl(add, [a:int, b:int], int)
│   └── Block
│       └── ReturnStatement(BinaryOp(+, a, b))
├── VariableDecl(x, 5)
├── VariableDecl(y, 3)
├── VariableDecl(result, FunctionCall(add, [x, y]))
└── WriteStatement(result)
```

### TAC Output
```
L0:     ; function add
t0 = a + b
return t0
L1:     ; main
t1 = 5
x = t1
t2 = 3
y = t2
push x
push y
t3 = call add
result = t3
write result
```

### MIPS Output
```asm
    .text
    .globl add
add:
    addi $sp, $sp, -8
    sw $ra, 4($sp)
    sw $fp, 0($sp)
    addi $fp, $sp, 8
    
    lw $t0, 0($fp)    ; load a
    lw $t1, 4($fp)    ; load b
    add $v0, $t0, $t1 ; add a + b
    
    lw $ra, 4($sp)
    lw $fp, 0($sp)
    addi $sp, $sp, 8
    jr $ra
```

---

## Compilation Options & Flags

### Build Configuration
- **Debug:** `CFLAGS = -g -Wall` (symbols, warnings)
- **Optimization:** Can add `-O2` for optimized builds
- **Platform:** Conditional settings for Windows/Unix

### Make Targets
| Target | Purpose |
|--------|---------|
| `all` | Build compiler executable |
| `clean` | Remove build artifacts |
| `test` | Run test suite |
| `lex.yy.c` | Generate lexer from flex spec |
| `parser.tab.c` | Generate parser from bison spec |

---

## Error Handling

### Compilation Errors
- **Lexical:** Invalid characters, unterminated strings
- **Syntax:** Invalid grammar constructs
- **Semantic:** Undefined variables, duplicate declarations
- **Runtime:** Division by zero, array bounds (in MIPS)

### Error Recovery
- Parser attempts to continue after syntax errors
- Helps identify multiple issues in one pass
- Prevents cascading errors

---

## Optimization Techniques

### Current Optimizations
1. **String Interning** - Deduplicate identical strings
2. **Memory Pooling** - Reduce malloc overhead
3. **Direct Register Allocation** - Minimize memory accesses

### Potential Future Optimizations
- Constant folding
- Dead code elimination
- Register allocation algorithms (graph coloring)
- Loop unrolling
- Instruction selection optimization

---

## Design Patterns

### Visitor Pattern
- AST traversal for semantic analysis
- Code generation traverses AST with code emitter

### Symbol Table Hash Map
- O(1) variable lookup
- Collision handling with chaining

### Memory Pool
- Pre-allocated chunks
- Reduces fragmentation
- Faster allocation than malloc

---

## Extending the Compiler

### Adding a New Language Feature

1. **Lexer:** Define token in `lexer.l`
2. **Parser:** Add grammar rule in `parser.y`
3. **AST:** Add node type in `AST.h`
4. **Semantic Analysis:** Update `symtab.c/h` if needed
5. **Code Generation:** Implement in `codegen.c/h`
6. **Testing:** Create test case

### Example: Adding While Loops
```
1. lexer.l:    Add WHILE token
2. parser.y:   Add while_stmt rule
3. AST.h:      Add NODE_STMT_WHILE type
4. codegen.c:  Implement codegen_while()
```

---

## Performance Characteristics

| Operation | Complexity | Implementation |
|-----------|-----------|-----------------|
| Variable lookup | O(1) | Hash table |
| Function lookup | O(1) | Hash table |
| AST construction | O(n) | n = source size |
| Code generation | O(m) | m = AST nodes |
| **Total** | **O(n)** | Linear pass |

---

## References

- [MIPS Assembly Language Guide](https://www.mips.com/)
- [Flex/Lex Manual](https://westes.github.io/flex/manual/)
- [Bison Parser Generator](https://www.gnu.org/software/bison/manual/)
- [Compilers: Principles, Techniques, and Tools](https://en.wikipedia.org/wiki/Compilers:_Principles,_Techniques,_and_Tools) (Dragon Book)

