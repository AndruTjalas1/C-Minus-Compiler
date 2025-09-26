#ifndef SYMTAB_H
#define SYMTAB_H

#define MAX_VARS 100

typedef struct Symbol {
    char* name;
    int offset;
    int size;               // total size (for arrays: rows * cols)
    int initial_value;
    char type;              // 'i' for int, 'c' for char
    int dimensions;         // 0 for scalar, 1 for 1D array, 2 for 2D array
    int dim1, dim2;         // array dimensions
} Symbol;

typedef struct SymbolTable {
    Symbol vars[MAX_VARS];
    int count;
    int nextOffset;
} SymbolTable;

extern SymbolTable symtab;

void initSymTab();
int addVar(char* name, int size, int initial_value, char type);
int addArray(char* name, int dim1, char type);
int add2DArray(char* name, int dim1, int dim2, char type);
int getVarOffset(const char* name);
int isVarDeclared(const char* name);
Symbol* getSymbol(const char* name);

#endif