#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AST.h"
#include "symtab.h"
#include "stringpool.h"

SymbolTable symtab;

// Hash function (djb2 algorithm)
unsigned int hash_symbol(const char* str) {
    unsigned int hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    return hash % HASH_SIZE;
}

void initSymTab() {
    memset(symtab.buckets, 0, sizeof(symtab.buckets));
    symtab.count = 0;
    symtab.nextOffset = 0;
    symtab.lookups = 0;
    symtab.collisions = 0;
    symtab.functions = NULL;
    symtab.currentFunction = NULL;
}

static Symbol* createSymbol(char* name) {
    Symbol* sym = malloc(sizeof(Symbol));
    sym->name = intern_string(name);  // Use string interning
    sym->offset = symtab.nextOffset;
    sym->size = 0;
    sym->initial_value = 0;
    sym->type = 0;
    sym->dimensions = 0;
    sym->dim1 = 1;
    sym->dim2 = 1;
    sym->initValues = NULL;
    sym->initCount = 0;
    sym->stringValue = NULL;
    sym->scope = symtab.currentFunction ? symtab.currentFunction->name : NULL;
    sym->next = NULL;
    return sym;
}

static void insertSymbol(Symbol* sym) {
    unsigned int bucket = hash_symbol(sym->name);
    
    // Check if bucket already has entries (collision)
    if (symtab.buckets[bucket] != NULL) {
        symtab.collisions++;
    }
    
    // Insert at head of chain
    sym->next = symtab.buckets[bucket];
    symtab.buckets[bucket] = sym;
    symtab.count++;
}

int addVar(char* name, int size, int initial_value, char type) {
    if (isVarDeclared(name)) {
        return -1;
    }
    if (symtab.count >= MAX_VARS) {
        fprintf(stderr, "Error: symbol table overflow\n");
        exit(1);
    }

    Symbol* sym = createSymbol(name);
    sym->size = size;
    sym->initial_value = initial_value;
    sym->type = type;

    if (type == 'c') {
        symtab.nextOffset += size;
    } else {
        symtab.nextOffset += size * 4;
    }
    
    insertSymbol(sym);
    return sym->offset;
}

int addArrayWithInit(char* name, int dim1, char type, int* initValues, int initCount) {
    if (isVarDeclared(name)) {
        return -1;
    }
    if (symtab.count >= MAX_VARS) {
        fprintf(stderr, "Error: symbol table overflow\n");
        exit(1);
    }

    Symbol* sym = createSymbol(name);
    sym->size = dim1;
    sym->type = type;
    sym->dimensions = 1;
    sym->dim1 = dim1;
    
    sym->initValues = malloc(dim1 * sizeof(int));
    sym->initCount = initCount;
    for (int i = 0; i < dim1; i++) {
        if (i < initCount) {
            sym->initValues[i] = initValues[i];
        } else {
            sym->initValues[i] = 0;
        }
    }

    if (type == 'c') {
        symtab.nextOffset += dim1;
    } else {
        symtab.nextOffset += dim1 * 4;
    }
    
    insertSymbol(sym);
    return sym->offset;
}

int addArray(char* name, int dim1, char type) {
    if (isVarDeclared(name)) {
        return -1;
    }
    if (symtab.count >= MAX_VARS) {
        fprintf(stderr, "Error: symbol table overflow\n");
        exit(1);
    }

    Symbol* sym = createSymbol(name);
    sym->size = dim1;
    sym->type = type;
    sym->dimensions = 1;
    sym->dim1 = dim1;

    if (type == 'c') {
        symtab.nextOffset += dim1;
    } else {
        symtab.nextOffset += dim1 * 4;
    }
    
    insertSymbol(sym);
    return sym->offset;
}

int add2DArray(char* name, int dim1, int dim2, char type) {
    if (isVarDeclared(name)) {
        return -1;
    }
    if (symtab.count >= MAX_VARS) {
        fprintf(stderr, "Error: symbol table overflow\n");
        exit(1);
    }

    Symbol* sym = createSymbol(name);
    sym->size = dim1 * dim2;
    sym->type = type;
    sym->dimensions = 2;
    sym->dim1 = dim1;
    sym->dim2 = dim2;

    if (type == 'c') {
        symtab.nextOffset += dim1 * dim2;
    } else {
        symtab.nextOffset += dim1 * dim2 * 4;
    }
    
    insertSymbol(sym);
    return sym->offset;
}

int add2DArrayWithInit(char* name, int dim1, int dim2, char type, int* initValues, int initCount) {
    if (isVarDeclared(name)) {
        return -1;
    }
    if (symtab.count >= MAX_VARS) {
        fprintf(stderr, "Error: symbol table overflow\n");
        exit(1);
    }

    Symbol* sym = createSymbol(name);
    sym->size = dim1 * dim2;
    sym->type = type;
    sym->dimensions = 2;
    sym->dim1 = dim1;
    sym->dim2 = dim2;
    
    sym->initValues = malloc(dim1 * dim2 * sizeof(int));
    sym->initCount = initCount;
    for (int i = 0; i < dim1 * dim2; i++) {
        if (i < initCount) {
            sym->initValues[i] = initValues[i];
        } else {
            sym->initValues[i] = 0;
        }
    }

    if (type == 'c') {
        symtab.nextOffset += dim1 * dim2;
    } else {
        symtab.nextOffset += dim1 * dim2 * 4;
    }
    
    insertSymbol(sym);
    return sym->offset;
}

int addStringVar(char* name, char* value) {
    if (isVarDeclared(name)) {
        return -1;
    }
    if (symtab.count >= MAX_VARS) {
        fprintf(stderr, "Error: symbol table overflow\n");
        exit(1);
    }

    int length = strlen(value) + 1;
    Symbol* sym = createSymbol(name);
    sym->type = 's';
    sym->size = length;
    sym->stringValue = intern_string(value);  // Use string interning
    
    symtab.nextOffset += length;
    insertSymbol(sym);
    return sym->offset;
}

int getVarOffset(const char* name) {
    symtab.lookups++;
    unsigned int bucket = hash_symbol(name);
    
    Symbol* sym = symtab.buckets[bucket];
    while (sym) {
        if (strcmp(sym->name, name) == 0) {
            return sym->offset;
        }
        sym = sym->next;
    }
    return -1;
}

int isVarDeclared(const char* name) {
    return getVarOffset(name) != -1;
}

Symbol* getSymbol(const char* name) {
    symtab.lookups++;
    unsigned int bucket = hash_symbol(name);
    
    Symbol* sym = symtab.buckets[bucket];
    while (sym) {
        if (strcmp(sym->name, name) == 0) {
            return sym;
        }
        sym = sym->next;
    }
    return NULL;
}

void print_symtab_stats() {
    printf("\n=== Symbol Table Statistics ===\n");
    printf("Total symbols: %d\n", symtab.count);
    printf("Total lookups: %d\n", symtab.lookups);
    printf("Collisions: %d\n", symtab.collisions);
    printf("Load factor: %.2f\n", (double)symtab.count / HASH_SIZE);
    
    // Calculate average chain length
    int used_buckets = 0;
    int max_chain = 0;
    for (int i = 0; i < HASH_SIZE; i++) {
        if (symtab.buckets[i]) {
            used_buckets++;
            int chain_len = 0;
            Symbol* sym = symtab.buckets[i];
            while (sym) {
                chain_len++;
                sym = sym->next;
            }
            if (chain_len > max_chain) {
                max_chain = chain_len;
            }
        }
    }
    printf("Used buckets: %d / %d (%.1f%%)\n", 
           used_buckets, HASH_SIZE, 
           (double)used_buckets / HASH_SIZE * 100.0);
    printf("Max chain length: %d\n", max_chain);
    if (used_buckets > 0) {
        printf("Average chain length: %.2f\n", 
               (double)symtab.count / used_buckets);
    }
}

/* ========== FUNCTION MANAGEMENT ========== */

int addFunction(char* name, char* returnType, struct ASTNode* params) {
    if (isFunctionDeclared(name)) {
        fprintf(stderr, "Error: Function '%s' already declared\n", name);
        return 0;
    }
    
    FunctionSymbol* func = malloc(sizeof(FunctionSymbol));
    func->name = intern_string(name);
    func->returnType = intern_string(returnType);
    
    // Count parameters
    int paramCount = 0;
    struct ASTNode* p = params;
    while (p) {
        paramCount++;
        p = p->next;
    }
    
    func->paramCount = paramCount;
    if (paramCount > 0) {
        func->paramTypes = malloc(paramCount * sizeof(char*));
        func->paramNames = malloc(paramCount * sizeof(char*));
        
        p = params;
        int i = 0;
        while (p) {
            func->paramTypes[i] = intern_string(p->returnType);
            func->paramNames[i] = intern_string(p->name);
            i++;
            p = p->next;
        }
    } else {
        func->paramTypes = NULL;
        func->paramNames = NULL;
    }
    
    func->stackSize = 0;
    func->next = symtab.functions;
    symtab.functions = func;
    
    return 1;
}

FunctionSymbol* getFunction(const char* name) {
    FunctionSymbol* func = symtab.functions;
    while (func) {
        if (strcmp(func->name, name) == 0) {
            return func;
        }
        func = func->next;
    }
    return NULL;
}

int isFunctionDeclared(const char* name) {
    return getFunction(name) != NULL;
}

int validateFunctionCall(const char* name, struct ASTNode* args) {
    FunctionSymbol* func = getFunction(name);
    if (!func) {
        fprintf(stderr, "Error: Undefined function '%s'\n", name);
        return 0;
    }
    
    // Count arguments
    int argCount = 0;
    struct ASTNode* arg = args;
    while (arg) {
        argCount++;
        arg = arg->next;
    }
    
    // Check parameter count
    if (argCount != func->paramCount) {
        fprintf(stderr, "Error: Function '%s' expects %d arguments, got %d\n",
                name, func->paramCount, argCount);
        return 0;
    }
    
    return 1;
}

void enterFunctionScope(const char* funcName) {
    FunctionSymbol* func = getFunction(funcName);
    if (!func) return;
    
    symtab.currentFunction = func;
    
    // Add parameters to symbol table as local variables
    for (int i = 0; i < func->paramCount; i++) {
        char varType;
        if (strcmp(func->paramTypes[i], "int") == 0) varType = 'i';
        else if (strcmp(func->paramTypes[i], "char") == 0) varType = 'c';
        else if (strcmp(func->paramTypes[i], "bool") == 0) varType = 'b';
        else if (strcmp(func->paramTypes[i], "string") == 0) varType = 's';
        else varType = 'i';
        
        addVar(func->paramNames[i], 1, 0, varType);
    }
}

void exitFunctionScope() {
    if (!symtab.currentFunction) return;
    symtab.currentFunction->stackSize = symtab.nextOffset;
    symtab.currentFunction = NULL;
}
