#ifndef ERROR_H
#define ERROR_H

// Error types
typedef enum {
    ERROR_SYNTAX,
    ERROR_SEMANTIC,
    ERROR_UNDECLARED_VARIABLE,
    ERROR_REDECLARED_VARIABLE,
    ERROR_TYPE_MISMATCH,
    ERROR_ARRAY_BOUNDS,
    ERROR_MISSING_SEMICOLON,
    ERROR_MISSING_PAREN,
    ERROR_MISSING_BRACE,
    ERROR_INVALID_OPERATOR,
    ERROR_DIVISION_BY_ZERO
} ErrorType;

// Error reporting function
void reportError(int line, const char* source, ErrorType type, const char* message);

// Specific error functions
void errorUndeclaredVariable(int line, const char* varName);
void errorRedeclaredVariable(int line, const char* varName);
void errorTypeMismatch(int line, const char* source, const char* expected, const char* actual);
void errorMissingSemicolon(int line, const char* source);
void errorMissingParen(int line, const char* source, const char* parenType);
void errorMissingBrace(int line, const char* source);
void errorArrayBounds(int line, const char* arrayName, int index, int size);

// Get error type string
const char* getErrorTypeString(ErrorType type);

#endif
