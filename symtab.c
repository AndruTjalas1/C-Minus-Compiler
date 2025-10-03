#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
