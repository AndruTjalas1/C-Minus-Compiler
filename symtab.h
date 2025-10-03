#ifndef SYMTAB_H
#define SYMTAB_H

#define HASH_SIZE 211  // Prime number for better distribution
#define MAX_VARS 1000  // Increased capacity

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
    struct Symbol* next;  // For hash chaining
} Symbol;

typedef struct SymbolTable {
    Symbol* buckets[HASH_SIZE];
    int count;
    int nextOffset;
    // Performance counters
    int lookups;
    int collisions;
} SymbolTable;

extern SymbolTable symtab;

// Hash function
unsigned int hash_symbol(const char* str);

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
void print_symtab_stats();

#endif
