#ifndef TAC_H
#define TAC_H

#include "AST.h"

/* TAC instruction opcodes */
typedef enum {
    TAC_ADD,
    TAC_SUB,
    TAC_MUL,
    TAC_DIV,
    TAC_PRINT,
    TAC_ASSIGN,
    TAC_VAR,
    TAC_NUM,
    TAC_CHAR,              // Add this for character literals
    TAC_ARRAY_DECL,
    TAC_ARRAY2D_DECL,
    TAC_ARRAY_ACCESS,      // Add this for array access
    TAC_ARRAY2D_ACCESS,    // Add this for 2D array access
    TAC_ARRAY_ASSIGN,      // Add this for array assignment
    TAC_ARRAY2D_ASSIGN     // Add this for 2D array assignment
} TACOp;

/* TAC instruction representation */
typedef struct TAC {
    TACOp op;
    char* res;       // result (lhs)
    char* arg1;      // operand 1
    char* arg2;      // operand 2 (NULL for unary ops)
    struct TAC* next;
} TAC;

/* TAC generation API */
void generateTAC(ASTNode* root, const char* filename);  // Main entry point
TAC* genTAC(ASTNode* root);   // Generate TAC from AST
void printTAC(TAC* code);     // Print TAC to stdout (for debugging)
TAC* concatTAC(TAC* a, TAC* b);
TAC* makeTAC(TACOp op, char* res, char* arg1, char* arg2);

#endif