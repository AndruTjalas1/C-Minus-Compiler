#ifndef SYMTAB_H
#define SYMTAB_H

#define MAX_VARS 100

typedef struct Symbol {
    char* name;
    int offset;
    int size;
    int initial_value;
    char type;          // 'i' for int, 'c' for char
} Symbol;

typedef struct SymbolTable {
    Symbol vars[MAX_VARS];
    int count;
    int nextOffset;
} SymbolTable;

extern SymbolTable symtab;

void initSymTab();
int addVar(char* name, int size, int initial_value, char type);
int getVarOffset(char* name);
int isVarDeclared(char* name);

#endif