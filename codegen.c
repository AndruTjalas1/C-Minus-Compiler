#include <stdio.h>
#include <string.h>
#include "AST.h"
#include "symtab.h"

/* Forward declarations */
void genExprMips(ASTNode* node, FILE* out);
void genStmtMips(ASTNode* node, FILE* out);
Symbol* lookupSymbol(const char* name);

/* Lookup helper */
Symbol* lookupSymbol(const char* name) {
    for (int i = 0; i < symtab.count; i++) {
        if (strcmp(symtab.vars[i].name, name) == 0)
            return &symtab.vars[i];
    }
    return NULL;
}

/* Generate MIPS for expressions */
void genExprMips(ASTNode* node, FILE* out) {
    if (!node) return;

    if (strcmp(node->type, "num") == 0) {
        fprintf(out, "    li $t0, %d\n", node->value);  // load immediate
    } 
    else if (strcmp(node->type, "char") == 0) {
        fprintf(out, "    li $t0, %d\n", node->value);  // load character as ASCII value
    } 
    else if (strcmp(node->type, "var") == 0) {
        Symbol* sym = lookupSymbol(node->name);
        if (!sym) {
            fprintf(stderr, "Error: undeclared variable '%s'\n", node->name);
            return;
        }
        if (sym->type == 'c')
            fprintf(out, "    lb $t0, %s\n", sym->name);  // load byte
        else
            fprintf(out, "    lw $t0, %s\n", sym->name);  // load word
    } 
    else if (strcmp(node->type, "binop") == 0) {
        genExprMips(node->left, out);
        fprintf(out, "    move $t1, $t0\n");            // save left operand
        genExprMips(node->right, out);              // right operand in $t0
        switch (node->op) {
            case '+': fprintf(out, "    add $t0, $t1, $t0\n"); break;
            case '-': fprintf(out, "    sub $t0, $t1, $t0\n"); break;
            case '*': fprintf(out, "    mul $t0, $t1, $t0\n"); break;
            case '/': fprintf(out, "    div $t1, $t0\n    mflo $t0\n"); break;
        }
    }
}

/* Generate MIPS for statements */
void genStmtMips(ASTNode* node, FILE* out) {
    ASTNode* p = node;
    while (p) {
        if (strcmp(p->type, "assign") == 0) {
            genExprMips(p->left, out);
            Symbol* sym = lookupSymbol(p->name);
            if (!sym) {
                fprintf(stderr, "Error: undeclared variable '%s'\n", p->name);
                return;
            }
            if (sym->type == 'c')
                fprintf(out, "    sb $t0, %s\n", sym->name);  // store byte
            else
                fprintf(out, "    sw $t0, %s\n", sym->name);  // store word
        }
        else if (strcmp(p->type, "print") == 0) {
            genExprMips(p->left, out);
            
            // Check if we're printing a variable to determine its type
            if (p->left && strcmp(p->left->type, "var") == 0) {
                Symbol* sym = lookupSymbol(p->left->name);
                if (sym && sym->type == 'c') {
                    fprintf(out, "    move $a0, $t0\n    li $v0, 11\n    syscall\n"); // print char
                } else {
                    fprintf(out, "    move $a0, $t0\n    li $v0, 1\n    syscall\n");  // print int
                }
            }
            // Check if we're printing a character literal
            else if (p->left && strcmp(p->left->type, "char") == 0) {
                fprintf(out, "    move $a0, $t0\n    li $v0, 11\n    syscall\n"); // print char
            }
            // Default to printing as integer
            else {
                fprintf(out, "    move $a0, $t0\n    li $v0, 1\n    syscall\n");  // print int
            }
            
            fprintf(out, "    li $a0, 10\n    li $v0, 11\n    syscall\n"); // newline
        }
        p = p->next;
    }
}

/* Entry point */
void generateMIPS(ASTNode* root, const char* filename) {
    FILE* out = fopen(filename, "w");
    if (!out) {
        perror(filename);
        return;
    }

    /* Data section */
    fprintf(out, ".data\n");
    for (int i = 0; i < symtab.count; i++) {
        Symbol* s = &symtab.vars[i];
        if (s->type == 'c') {
            if (s->size == 1)
                fprintf(out, "%s: .byte %d\n", s->name, s->initial_value);
            else
                fprintf(out, "%s: .space %d\n", s->name, s->size);
        } else { // int
            if (s->size == 1)
                fprintf(out, "%s: .word %d\n", s->name, s->initial_value);
            else
                fprintf(out, "%s: .space %d\n", s->name, s->size * 4);
        }
    }

    /* Text section */
    fprintf(out, ".text\n.globl main\nmain:\n");

    /* Generate code for all statements */
    genStmtMips(root, out);

    fprintf(out, "    li $v0, 10\n    syscall\n"); // exit
    fclose(out);
}