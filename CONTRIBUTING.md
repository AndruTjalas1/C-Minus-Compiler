# Contributing to c-minus-compiler

Thank you for your interest in contributing! We welcome improvements, bug fixes, and new features.

## Code of Conduct

- Be respectful and professional
- Provide constructive feedback
- Focus on ideas and code, not personal criticism
- Help others learn and grow

## How to Contribute

### 1. Reporting Bugs

**Before reporting:**
- Check existing issues to avoid duplicates
- Verify the issue with the latest build

**When reporting:**
- Use clear, descriptive title
- Include steps to reproduce
- Provide expected vs. actual behavior
- Include compiler version: `./Compiler --version` (if available)
- Include test case code if applicable

**Example issue:**
```
Title: Parser fails on nested array declarations

Description:
The compiler crashes when parsing multi-dimensional array 
declarations in function parameters.

Steps to reproduce:
1. Create file: int matrix[3][3]; int x = matrix[0][0];
2. Run: ./Compiler test.c output.s
3. Error: Segmentation fault

Expected: Should compile successfully
Actual: Segmentation fault

Test case: [attached code]
```

### 2. Suggesting Enhancements

**Good enhancement ideas:**
- New language features (break, continue, switch)
- Better error messages
- Additional built-in functions
- Performance improvements
- Better documentation
- Test coverage

**Poor enhancement ideas:**
- Major architectural changes without discussion
- Features contradicting language design
- Undocumented breaking changes

**Proposal template:**
```
Title: Add break and continue statements

Motivation:
Currently, loops require flag variables to exit. Break/continue
would simplify loop control.

Proposed Implementation:
1. Add BREAK, CONTINUE tokens to lexer
2. Add break_stmt and continue_stmt to parser
3. Add code generation in codegen.c
4. Update documentation

Example usage:
for (i = 0; i < 10; i++) {
    if (i == 5) continue;
    if (i == 8) break;
    write(i);
}
```

### 3. Submitting Code Changes

#### Fork and Clone
```bash
# Fork on GitHub, then clone your fork
git clone https://github.com/YOUR_USERNAME/c-minus-compiler.git
cd c-minus-compiler
```

#### Create Feature Branch
```bash
# Create descriptive branch name
git checkout -b feature/break-continue
# or
git checkout -b fix/parser-array-bug
# or
git checkout -b docs/improve-architecture
```

#### Make Changes

Follow our [Code Style Guide](#code-style-guide)

```bash
# Make your changes
# Test thoroughly
make clean
make
make test

# Commit with clear message
git commit -m "Add break and continue support

- Implement BREAK and CONTINUE tokens in lexer
- Add grammar rules to parser
- Generate proper MIPS labels and jumps
- Includes comprehensive tests"
```

#### Push and Create Pull Request
```bash
git push origin feature/break-continue
```

Then create a PR on GitHub with:
- Clear title and description
- Reference to related issues
- Test results

---

## Code Style Guide

### C Code Standards

#### Naming Conventions
```c
// Functions: lowercase_with_underscores
void create_ast_node() { }
int calculate_offset() { }

// Variables: lowercase_with_underscores
int symbol_count;
char* identifier_name;

// Constants: UPPERCASE_WITH_UNDERSCORES
#define MAX_SYMBOLS 1024
#define DEFAULT_BUFFER_SIZE 256

// Types: Capitalize_With_Underscores
typedef struct {
    int value;
} My_Type;

// Enum values: UPPERCASE
enum { TAC_ASSIGN, TAC_BINARY_OP };
```

#### Indentation and Formatting
```c
// Use 4-space indentation
if (condition) {
    statement1;
    statement2;
}

// Opening brace on same line
function_call() {
    do_something();
}

// One variable per line in declarations
int x;
int y;
int z;

// Binary operators have spaces
int result = a + b * c;

// Function declarations on one line if short
void init_module();

// Otherwise, put on separate lines
void complex_function(
    int parameter1,
    char* parameter2,
    int parameter3
);
```

#### Comments and Documentation
```c
// Single-line comment for brief explanations
x = y + 1;  // Increment counter

// Multi-line comments for complex logic
/*
 * Complex algorithm explanation here:
 * - Step 1: Initialize
 * - Step 2: Process
 * - Step 3: Finalize
 */

// Function documentation (if applicable)
/**
 * Allocates an AST node from the memory pool.
 * @param type The node type
 * @return Pointer to new node, or NULL if pool exhausted
 */
ASTNode* create_ast_node(ASTNodeType type);
```

#### Memory Management
```c
// Always check malloc return
char* buffer = malloc(size);
if (!buffer) {
    perror("malloc failed");
    return NULL;
}

// Use consistent cleanup
free(buffer);
buffer = NULL;

// In callbacks, document ownership
// Caller owns returned memory
char* get_name() {
    return malloc(20);  // Caller must free
}

// Function owns argument
void process_name(char* name) {
    free(name);  // Function responsible for cleanup
}
```

#### Error Handling
```c
// Check return values
FILE* f = fopen(filename, "r");
if (!f) {
    fprintf(stderr, "Error: Cannot open %s\n", filename);
    return ERROR_CODE;
}

// Propagate errors up
if (parse_expression() != SUCCESS) {
    return PARSE_ERROR;
}

// Use meaningful error codes
#define SUCCESS 0
#define PARSE_ERROR -1
#define SEMANTIC_ERROR -2
#define CODEGEN_ERROR -3
```

### Flex Lexer Style
```flex
/* Group related patterns */
[0-9]+      { return INTEGER; }
[a-zA-Z_][a-zA-Z0-9_]* { return IDENTIFIER; }

/* Use meaningful comments */
"&&"        { /* Logical AND */ return AND; }

/* Keep action blocks short */
"+"         { return PLUS; }
```

### Bison Parser Style
```bison
/* Clear rule names */
program: declarations statements { $$ = make_program($1, $2); }

/* Indent productions */
function_decl:
    FUNCTION type IDENTIFIER LPAREN params RPAREN block
    {
        $$ = make_function_decl($2, $3, $5, $7);
    }

/* Document conflicts if necessary */
/* Expect 2 shift/reduce conflicts for dangling else */
%expect 2
```

### Documentation Files (Markdown)
- Use proper Markdown syntax
- Include code blocks with language specification
- Use headers appropriately
- Keep lines reasonably short for readability
- Include examples where applicable

---

## Development Workflow

### Setting Up Development Environment

```bash
# Clone the repository
git clone https://github.com/YOUR_USERNAME/c-minus-compiler.git
cd c-minus-compiler

# Create development branch
git checkout -b dev/my-feature

# Build with debug flags
CFLAGS="-g -Wall -O0" make clean make

# Verify everything works
make test
```

### Testing Your Changes

#### Run Existing Tests
```bash
make test
```

#### Create New Tests
Add test files to document your feature:

```bash
# Create test file: test_my_feature.c
cat > test_my_feature.c << 'EOF'
// Test break statement
int i;
for (i = 0; i < 10; i++) {
    if (i == 5) {
        break;
    }
    write(i);
}
// Expected output: 0 1 2 3 4
EOF

# Test your implementation
./Compiler test_my_feature.c output.s
spim -file output.s
```

#### Verify No Regressions
```bash
# Run all existing tests
for f in test*.c; do
    echo "Testing $f..."
    ./Compiler "$f" out.s
    spim -file out.s
done
```

#### Add to Comprehensive Test
If your feature is significant, add to `comprehensive_test.cm`

### Debugging

#### Print Debug Information
```c
#ifdef DEBUG
fprintf(stderr, "DEBUG: variable=%d\n", value);
#endif
```

Compile with:
```bash
CFLAGS="-g -Wall -DDEBUG" make
```

#### Use GDB
```bash
# Build with debug symbols (default with -g)
make clean
make

# Run under GDB
gdb ./Compiler
(gdb) run test.c output.s
(gdb) backtrace  # If crashes
(gdb) quit
```

#### Check Generated Code
```bash
# Examine generated MIPS
cat output.s

# Run with SPIM verbose
spim -file output.s -dump

# Check for obvious issues
grep "undefined" output.s  # Look for undefined symbols
```

---

## Submission Guidelines

### Before Submitting PR

- [ ] Code compiles without warnings: `make clean && make`
- [ ] All existing tests pass: `make test`
- [ ] New tests pass: `./Compiler test_feature.c output.s`
- [ ] No memory leaks (if possible to check)
- [ ] Code follows style guide
- [ ] Comments explain non-obvious logic
- [ ] Commits have clear messages

### PR Description Template

```markdown
## Description
Brief description of changes

## Motivation and Context
Why is this change needed? What problem does it solve?

## Type of Change
- [ ] Bug fix
- [ ] New feature
- [ ] Enhancement
- [ ] Documentation
- [ ] Performance improvement

## How Has This Been Tested?
Describe test coverage:
- [ ] Existing tests still pass
- [ ] New tests added
- [ ] Manual testing performed

## Test Cases
Provide example code demonstrating the feature/fix:

```c
// Example test code
function int test() {
    // ...
}
```

## Checklist
- [ ] Code compiles without errors
- [ ] Code compiles without warnings
- [ ] Tests pass
- [ ] Documentation updated
- [ ] Commits have clear messages
```

---

## Area-Specific Guidelines

### Adding Language Features

1. **Lexer** (`lexer.l`)
   - Add new token pattern
   - Test with various inputs

2. **Parser** (`parser.y`)
   - Add grammar rule
   - Handle precedence if needed
   - Check for conflicts: `make` will show shift/reduce warnings

3. **AST** (`AST.h/c`)
   - Add node type
   - Update create/destroy functions

4. **Codegen** (`codegen.c`)
   - Implement code generation
   - Test with SPIM

### Fixing Bugs

1. **Create minimal test case** that reproduces the bug
2. **Identify the phase** where bug occurs (lexer/parser/codegen)
3. **Fix the issue** in that phase
4. **Verify** the fix doesn't break existing functionality
5. **Add test case** to prevent regression

### Improving Documentation

- Keep markdown properly formatted
- Check links are correct
- Run `make` to verify examples still work
- Keep documentation synchronized with code

---

## Getting Help

- **Questions?** Open a GitHub discussion
- **Issues?** Search existing issues first
- **Stuck?** Ask in a GitHub issue or discussion
- **Want to discuss architecture?** Start a discussion

---

## Recognition

Contributors will be recognized in:
- Project README (contributors section)
- Release notes for significant contributions
- Code comments where appropriate

---

## Review Process

1. **Automated checks**
   - Code compiles
   - Tests pass
   - No obvious style violations

2. **Code review**
   - At least one maintainer review
   - Feedback on design and implementation
   - Request for changes if needed

3. **Approval**
   - All comments addressed
   - All checks passing
   - Ready to merge

4. **Merge**
   - Squash or rebase as appropriate
   - Close associated issues

---

## License

By contributing, you agree that your contributions will be licensed under the MIT License.

---

Thank you for contributing to c-minus-compiler! 🙏

