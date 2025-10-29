#include <stdio.h>
#include <stdlib.h>
#include "error.h"

// Color codes for terminal output
#define COLOR_RED     "\x1b[31m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_RESET   "\x1b[0m"
#define COLOR_BOLD    "\x1b[1m"

// Get error type string
const char* getErrorTypeString(ErrorType type) {
    switch(type) {
        case ERROR_SYNTAX:              return "Syntax Error";
        case ERROR_SEMANTIC:            return "Semantic Error";
        case ERROR_UNDECLARED_VARIABLE: return "Undeclared Variable";
        case ERROR_REDECLARED_VARIABLE: return "Redeclared Variable";
        case ERROR_TYPE_MISMATCH:       return "Type Mismatch";
        case ERROR_ARRAY_BOUNDS:        return "Array Bounds Error";
        case ERROR_MISSING_SEMICOLON:   return "Missing Semicolon";
        case ERROR_MISSING_PAREN:       return "Missing Parenthesis";
        case ERROR_MISSING_BRACE:       return "Missing Brace";
        case ERROR_INVALID_OPERATOR:    return "Invalid Operator";
        case ERROR_DIVISION_BY_ZERO:    return "Division by Zero";
        default:                        return "Unknown Error";
    }
}

// Main error reporting function
void reportError(int line, const char* source, ErrorType type, const char* message) {
    fprintf(stderr, "\n");
    fprintf(stderr, "%s%sError at line %d%s", COLOR_RED, COLOR_BOLD, line, COLOR_RESET);
    
    if (source && source[0] != '\0') {
        fprintf(stderr, " %s(%s)%s", COLOR_YELLOW, source, COLOR_RESET);
    }
    
    fprintf(stderr, ":\n");
    fprintf(stderr, "  %s%s%s: %s\n", COLOR_BOLD, getErrorTypeString(type), COLOR_RESET, message);
    fprintf(stderr, "\n");
}

// Specific error functions
void errorUndeclaredVariable(int line, const char* varName) {
    char message[256];
    snprintf(message, sizeof(message), "Variable '%s' used before declaration", varName);
    reportError(line, varName, ERROR_UNDECLARED_VARIABLE, message);
}

void errorRedeclaredVariable(int line, const char* varName) {
    char message[256];
    snprintf(message, sizeof(message), "Variable '%s' has already been declared in this scope", varName);
    reportError(line, varName, ERROR_REDECLARED_VARIABLE, message);
}

void errorTypeMismatch(int line, const char* source, const char* expected, const char* actual) {
    char message[256];
    snprintf(message, sizeof(message), "Expected type '%s' but got '%s'", expected, actual);
    reportError(line, source, ERROR_TYPE_MISMATCH, message);
}

void errorMissingSemicolon(int line, const char* source) {
    reportError(line, source, ERROR_MISSING_SEMICOLON, 
                "Statement must end with a semicolon ';'");
}

void errorMissingParen(int line, const char* source, const char* parenType) {
    char message[256];
    snprintf(message, sizeof(message), "Missing %s parenthesis", parenType);
    reportError(line, source, ERROR_MISSING_PAREN, message);
}

void errorMissingBrace(int line, const char* source) {
    reportError(line, source, ERROR_MISSING_BRACE, 
                "Missing closing brace '}'");
}

void errorArrayBounds(int line, const char* arrayName, int index, int size) {
    char message[256];
    char source[256];
    snprintf(source, sizeof(source), "%s[%d]", arrayName, index);
    snprintf(message, sizeof(message), 
             "Array index %d is out of bounds (array size is %d)", index, size);
    reportError(line, source, ERROR_ARRAY_BOUNDS, message);
}

void errorFunctionArgTypeMismatch(int line, const char* funcName, int paramNum, const char* expected, const char* actual) {
    char message[256];
    char source[256];
    snprintf(source, sizeof(source), "%s(param %d)", funcName, paramNum);
    snprintf(message, sizeof(message), 
             "Parameter %d expects type '%s' but got '%s'", paramNum, expected, actual);
    reportError(line, source, ERROR_TYPE_MISMATCH, message);
}
