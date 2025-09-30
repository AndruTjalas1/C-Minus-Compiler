#ifndef SYMTAB_H
#define SYMTAB_H

#define MAX_VARS 100

typedef struct Symbol {
    char* name;
    int offset;
    int size;
    int initial_value;
    char type;
    int dimensions;
    int dim1, dim2;
    int* initValues;
    int initCount;
    char* stringValue;
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
int addArrayWithInit(char* name, int dim1, char type, int* initValues, int initCount);
int add2DArray(char* name, int dim1, int dim2, char type);
int add2DArrayWithInit(char* name, int dim1, int dim2, char type, int* initValues, int initCount);
int addStringVar(char* name, char* value);
int getVarOffset(const char* name);
int isVarDeclared(const char* name);
Symbol* getSymbol(const char* name);

#endif