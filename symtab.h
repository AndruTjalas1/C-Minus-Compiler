#ifndef SYMTAB_H
#define SYMTAB_H

// Forward declaration to avoid circular dependency
struct ASTNode;

#define HASH_SIZE 211  // Prime number for better distribution
#define MAX_VARS 1000  // Increased capacity

typedef struct FunctionSymbol {
    char* name;
    char* returnType;
    int paramCount;
    char** paramTypes;
    char** paramNames;
    int* isArrayParam;        // 1 if param is array, 0 otherwise
    int* arrayParamDim1;      // First dimension (0 if variable-length)
    int* arrayParamDim2;      // Second dimension (0 if variable-length)
    int stackSize;
    struct FunctionSymbol* next;
} FunctionSymbol;

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
    char* scope;  // Function scope (NULL for global variables)
    int isArrayParam;         // 1 if this is an array parameter
    int arrayLength;          // Length passed for variable-length array params (-1 if not applicable)
    struct Symbol* next;  // For hash chaining
} Symbol;

typedef struct SymbolTable {
    Symbol* buckets[HASH_SIZE];
    FunctionSymbol* functions;
    FunctionSymbol* currentFunction;
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
int addArrayParam(char* name, int dim1, int dim2, char type, int arrayLength);
int addArray(char* name, int dim1, char type);
int addArrayWithInit(char* name, int dim1, char type, int* initValues, int initCount);
int add2DArray(char* name, int dim1, int dim2, char type);
int add2DArrayWithInit(char* name, int dim1, int dim2, char type, int* initValues, int initCount);
int addStringVar(char* name, char* value);
int getVarOffset(const char* name);
int isVarDeclared(const char* name);
Symbol* getSymbol(const char* name);
void print_symtab_stats();

// Function management
int addFunction(char* name, char* returnType, struct ASTNode* params);
FunctionSymbol* getFunction(const char* name);
int isFunctionDeclared(const char* name);
int validateFunctionCall(const char* name, struct ASTNode* args);
void enterFunctionScope(const char* funcName);
void exitFunctionScope();

#endif
