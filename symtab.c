#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

SymbolTable symtab;

void initSymTab() {
    symtab.count = 0;
    symtab.nextOffset = 0;
}

int addVar(char* name, int size, int initial_value, char type) {
    if (isVarDeclared(name)) {
        return -1;
    }
    if (symtab.count >= MAX_VARS) {
        fprintf(stderr, "Error: symbol table overflow\n");
        exit(1);
    }

    symtab.vars[symtab.count].name = strdup(name);
    symtab.vars[symtab.count].offset = symtab.nextOffset;
    symtab.vars[symtab.count].size = size;
    symtab.vars[symtab.count].initial_value = initial_value;
    symtab.vars[symtab.count].type = type;
    symtab.vars[symtab.count].dimensions = 0;
    symtab.vars[symtab.count].dim1 = 1;
    symtab.vars[symtab.count].dim2 = 1;
    symtab.vars[symtab.count].initValues = NULL;
    symtab.vars[symtab.count].initCount = 0;
    symtab.vars[symtab.count].stringValue = NULL;

    if (type == 'c') {
        symtab.nextOffset += size;
    } else {
        symtab.nextOffset += size * 4;
    }
    
    symtab.count++;
    return symtab.vars[symtab.count - 1].offset;
}

int addArrayWithInit(char* name, int dim1, char type, int* initValues, int initCount) {
    if (isVarDeclared(name)) {
        return -1;
    }
    if (symtab.count >= MAX_VARS) {
        fprintf(stderr, "Error: symbol table overflow\n");
        exit(1);
    }

    symtab.vars[symtab.count].name = strdup(name);
    symtab.vars[symtab.count].offset = symtab.nextOffset;
    symtab.vars[symtab.count].size = dim1;
    symtab.vars[symtab.count].initial_value = 0;
    symtab.vars[symtab.count].type = type;
    symtab.vars[symtab.count].dimensions = 1;
    symtab.vars[symtab.count].dim1 = dim1;
    symtab.vars[symtab.count].dim2 = 1;
    symtab.vars[symtab.count].stringValue = NULL;
    
    symtab.vars[symtab.count].initValues = malloc(dim1 * sizeof(int));
    symtab.vars[symtab.count].initCount = initCount;
    for (int i = 0; i < dim1; i++) {
        if (i < initCount) {
            symtab.vars[symtab.count].initValues[i] = initValues[i];
        } else {
            symtab.vars[symtab.count].initValues[i] = 0;
        }
    }

    if (type == 'c') {
        symtab.nextOffset += dim1;
    } else {
        symtab.nextOffset += dim1 * 4;
    }
    
    symtab.count++;
    return symtab.vars[symtab.count - 1].offset;
}

int addArray(char* name, int dim1, char type) {
    if (isVarDeclared(name)) {
        return -1;
    }
    if (symtab.count >= MAX_VARS) {
        fprintf(stderr, "Error: symbol table overflow\n");
        exit(1);
    }

    symtab.vars[symtab.count].name = strdup(name);
    symtab.vars[symtab.count].offset = symtab.nextOffset;
    symtab.vars[symtab.count].size = dim1;
    symtab.vars[symtab.count].initial_value = 0;
    symtab.vars[symtab.count].type = type;
    symtab.vars[symtab.count].dimensions = 1;
    symtab.vars[symtab.count].dim1 = dim1;
    symtab.vars[symtab.count].dim2 = 1;
    symtab.vars[symtab.count].initValues = NULL;
    symtab.vars[symtab.count].initCount = 0;
    symtab.vars[symtab.count].stringValue = NULL;

    if (type == 'c') {
        symtab.nextOffset += dim1;
    } else {
        symtab.nextOffset += dim1 * 4;
    }
    
    symtab.count++;
    return symtab.vars[symtab.count - 1].offset;
}

int add2DArray(char* name, int dim1, int dim2, char type) {
    if (isVarDeclared(name)) {
        return -1;
    }
    if (symtab.count >= MAX_VARS) {
        fprintf(stderr, "Error: symbol table overflow\n");
        exit(1);
    }

    symtab.vars[symtab.count].name = strdup(name);
    symtab.vars[symtab.count].offset = symtab.nextOffset;
    symtab.vars[symtab.count].size = dim1 * dim2;
    symtab.vars[symtab.count].initial_value = 0;
    symtab.vars[symtab.count].type = type;
    symtab.vars[symtab.count].dimensions = 2;
    symtab.vars[symtab.count].dim1 = dim1;
    symtab.vars[symtab.count].dim2 = dim2;
    symtab.vars[symtab.count].initValues = NULL;
    symtab.vars[symtab.count].initCount = 0;
    symtab.vars[symtab.count].stringValue = NULL;

    if (type == 'c') {
        symtab.nextOffset += dim1 * dim2;
    } else {
        symtab.nextOffset += dim1 * dim2 * 4;
    }
    
    symtab.count++;
    return symtab.vars[symtab.count - 1].offset;
}

int add2DArrayWithInit(char* name, int dim1, int dim2, char type, int* initValues, int initCount) {
    if (isVarDeclared(name)) {
        return -1;
    }
    if (symtab.count >= MAX_VARS) {
        fprintf(stderr, "Error: symbol table overflow\n");
        exit(1);
    }

    symtab.vars[symtab.count].name = strdup(name);
    symtab.vars[symtab.count].offset = symtab.nextOffset;
    symtab.vars[symtab.count].size = dim1 * dim2;
    symtab.vars[symtab.count].initial_value = 0;
    symtab.vars[symtab.count].type = type;
    symtab.vars[symtab.count].dimensions = 2;
    symtab.vars[symtab.count].dim1 = dim1;
    symtab.vars[symtab.count].dim2 = dim2;
    symtab.vars[symtab.count].stringValue = NULL;
    
    // Allocate and copy initialization values
    symtab.vars[symtab.count].initValues = malloc(dim1 * dim2 * sizeof(int));
    symtab.vars[symtab.count].initCount = initCount;
    for (int i = 0; i < dim1 * dim2; i++) {
        if (i < initCount) {
            symtab.vars[symtab.count].initValues[i] = initValues[i];
        } else {
            symtab.vars[symtab.count].initValues[i] = 0;
        }
    }

    if (type == 'c') {
        symtab.nextOffset += dim1 * dim2;
    } else {
        symtab.nextOffset += dim1 * dim2 * 4;
    }
    
    symtab.count++;
    return symtab.vars[symtab.count - 1].offset;
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
    symtab.vars[symtab.count].name = strdup(name);
    symtab.vars[symtab.count].offset = symtab.nextOffset;
    symtab.vars[symtab.count].type = 's';
    symtab.vars[symtab.count].dimensions = 0;
    symtab.vars[symtab.count].size = length;
    symtab.vars[symtab.count].initial_value = 0;
    symtab.vars[symtab.count].dim1 = 1;
    symtab.vars[symtab.count].dim2 = 1;
    symtab.vars[symtab.count].initValues = NULL;
    symtab.vars[symtab.count].initCount = 0;
    symtab.vars[symtab.count].stringValue = strdup(value);
    
    symtab.nextOffset += length;
    symtab.count++;
    return symtab.vars[symtab.count - 1].offset;
}

int getVarOffset(const char* name) {
    for (int i = 0; i < symtab.count; i++) {
        if (strcmp(symtab.vars[i].name, name) == 0)
            return symtab.vars[i].offset;
    }
    return -1;
}

int isVarDeclared(const char* name) {
    return getVarOffset(name) != -1;
}

Symbol* getSymbol(const char* name) {
    for (int i = 0; i < symtab.count; i++) {
        if (strcmp(symtab.vars[i].name, name) == 0)
            return &symtab.vars[i];
    }
    return NULL;
}