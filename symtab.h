#ifndef SYMTAB_H
#define SYMTAB_H

#define MAX_VARS 100

typedef struct {
    char* name;
    int offset;         // stack offset
    int size;           // 1 for scalar, >1 for arrays
    int initial_value;  // only used for scalar initialization
} Symbol;

typedef struct {
    Symbol vars[MAX_VARS];
    int count;
    int nextOffset;     // stack grows by 4 bytes per int
} SymbolTable;

extern SymbolTable symtab;

void initSymTab();
int addVar(char* name, int size, int initial_value);
int getVarOffset(char* name);
int isVarDeclared(char* name);

#endif
