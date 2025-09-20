#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symtab.h"

SymbolTable symtab;

void initSymTab() {
    symtab.count = 0;
    symtab.nextOffset = 0;
}

int addVar(char* name, int size, int initial_value) {
    if (isVarDeclared(name)) {
        return -1; // already declared
    }
    if (symtab.count >= MAX_VARS) {
        fprintf(stderr, "Error: symbol table overflow\n");
        exit(1);
    }

    symtab.vars[symtab.count].name = strdup(name);
    symtab.vars[symtab.count].offset = symtab.nextOffset;
    symtab.vars[symtab.count].size = size;
    symtab.vars[symtab.count].initial_value = initial_value;

    symtab.nextOffset += size * 4;
    symtab.count++;
    return symtab.vars[symtab.count - 1].offset;
}

int getVarOffset(char* name) {
    for (int i = 0; i < symtab.count; i++) {
        if (strcmp(symtab.vars[i].name, name) == 0)
            return symtab.vars[i].offset;
    }
    return -1;
}

int isVarDeclared(char* name) {
    return getVarOffset(name) != -1;
}
