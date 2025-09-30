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
    return getSymbol(name);
}

/* Generate MIPS for expressions */
void genExprMips(ASTNode* node, FILE* out) {
    if (!node) return;

    if (strcmp(node->type, "num") == 0) {
        fprintf(out, "    li $t0, %d\n", node->value);
    }
    else if (strcmp(node->type, "char") == 0) {
        fprintf(out, "    li $t0, %d\n", node->value);
    } 
    else if (strcmp(node->type, "var") == 0) {
        Symbol* sym = lookupSymbol(node->name);
        if (!sym) {
            fprintf(stderr, "Error: undeclared variable '%s'\n", node->name);
            return;
        }
        // Check if it's a string variable
        if (sym->stringValue) {
            fprintf(out, "    la $t0, %s\n", sym->name);  // load string address
        }
        else if (sym->type == 'c') {
            fprintf(out, "    lb $t0, %s\n", sym->name);
        }
        else {
            fprintf(out, "    lw $t0, %s\n", sym->name);
        }
    }
    else if (strcmp(node->type, "array_access") == 0) {
        Symbol* sym = lookupSymbol(node->name);
        if (!sym) {
            fprintf(stderr, "Error: undeclared array '%s'\n", node->name);
            return;
        }
        
        genExprMips(node->left, out);
        
        if (sym->type == 'c') {
            fprintf(out, "    la $t1, %s\n", sym->name);
            fprintf(out, "    add $t1, $t1, $t0\n");
            fprintf(out, "    lb $t0, 0($t1)\n");
        } else {
            fprintf(out, "    sll $t0, $t0, 2\n");
            fprintf(out, "    la $t1, %s\n", sym->name);
            fprintf(out, "    add $t1, $t1, $t0\n");
            fprintf(out, "    lw $t0, 0($t1)\n");
        }
    }
    else if (strcmp(node->type, "array2d_access") == 0) {
        Symbol* sym = lookupSymbol(node->name);
        if (!sym) {
            fprintf(stderr, "Error: undeclared array '%s'\n", node->name);
            return;
        }
        
        genExprMips(node->left, out);
        fprintf(out, "    move $t2, $t0\n");
        fprintf(out, "    li $t3, %d\n", sym->dim2);
        fprintf(out, "    mul $t2, $t2, $t3\n");
        
        genExprMips(node->right, out);
        fprintf(out, "    add $t0, $t2, $t0\n");
        
        if (sym->type == 'c') {
            fprintf(out, "    la $t1, %s\n", sym->name);
            fprintf(out, "    add $t1, $t1, $t0\n");
            fprintf(out, "    lb $t0, 0($t1)\n");
        } else {
            fprintf(out, "    sll $t0, $t0, 2\n");
            fprintf(out, "    la $t1, %s\n", sym->name);
            fprintf(out, "    add $t1, $t1, $t0\n");
            fprintf(out, "    lw $t0, 0($t1)\n");
        }
    } 
    else if (strcmp(node->type, "binop") == 0) {
        fprintf(out, "    sw $s0, -4($sp)\n");
        fprintf(out, "    addiu $sp, $sp, -4\n");

        genExprMips(node->left, out);
        fprintf(out, "    move $s0, $t0\n");
        genExprMips(node->right, out);
        switch (node->op) {
            case '+': fprintf(out, "    add $t0, $s0, $t0\n"); break;
            case '-': fprintf(out, "    sub $t0, $s0, $t0\n"); break;
            case '*': fprintf(out, "    mul $t0, $s0, $t0\n"); break;
            case '/': fprintf(out, "    div $s0, $t0\n    mflo $t0\n"); break;
        }

        fprintf(out, "    addiu $sp, $sp, 4\n");
        fprintf(out, "    lw $s0, -4($sp)\n");
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
                fprintf(out, "    sb $t0, %s\n", sym->name);
            else
                fprintf(out, "    sw $t0, %s\n", sym->name);
        }
        else if (strcmp(p->type, "string_decl") == 0) {
            // Strings initialized in data section
        }
        else if (strcmp(p->type, "array_decl_init") == 0) {
            Symbol* sym = lookupSymbol(p->name);
            if (!sym || !sym->initValues) {
                p = p->next;
                continue;
            }
            
            for (int i = 0; i < sym->initCount && i < sym->dim1; i++) {
                fprintf(out, "    li $t0, %d\n", sym->initValues[i]);
                fprintf(out, "    li $t1, %d\n", i);
                
                if (sym->type == 'c') {
                    fprintf(out, "    la $t2, %s\n", sym->name);
                    fprintf(out, "    add $t2, $t2, $t1\n");
                    fprintf(out, "    sb $t0, 0($t2)\n");
                } else {
                    fprintf(out, "    sll $t1, $t1, 2\n");
                    fprintf(out, "    la $t2, %s\n", sym->name);
                    fprintf(out, "    add $t2, $t2, $t1\n");
                    fprintf(out, "    sw $t0, 0($t2)\n");
                }
            }
        }
        else if (strcmp(p->type, "array2d_decl_init") == 0) {
            Symbol* sym = lookupSymbol(p->name);
            if (!sym || !sym->initValues) {
                p = p->next;
                continue;
            }
            
            // Initialize 2D array elements in row-major order
            for (int i = 0; i < sym->initCount && i < (sym->dim1 * sym->dim2); i++) {
                fprintf(out, "    li $t0, %d\n", sym->initValues[i]);
                fprintf(out, "    li $t1, %d\n", i);
                
                if (sym->type == 'c') {
                    fprintf(out, "    la $t2, %s\n", sym->name);
                    fprintf(out, "    add $t2, $t2, $t1\n");
                    fprintf(out, "    sb $t0, 0($t2)\n");
                } else {
                    fprintf(out, "    sll $t1, $t1, 2\n");
                    fprintf(out, "    la $t2, %s\n", sym->name);
                    fprintf(out, "    add $t2, $t2, $t1\n");
                    fprintf(out, "    sw $t0, 0($t2)\n");
                }
            }
        }
        else if (strcmp(p->type, "array_assign") == 0) {
            genExprMips(p->right, out);
            fprintf(out, "    move $t9, $t0\n");
            
            ASTNode* arrayAccess = p->left;
            Symbol* sym = lookupSymbol(arrayAccess->name);
            if (!sym) {
                fprintf(stderr, "Error: undeclared array '%s'\n", arrayAccess->name);
                return;
            }
            
            if (strcmp(arrayAccess->type, "array_access") == 0) {
                genExprMips(arrayAccess->left, out);
                
                if (sym->type == 'c') {
                    fprintf(out, "    la $t1, %s\n", sym->name);
                    fprintf(out, "    add $t1, $t1, $t0\n");
                    fprintf(out, "    sb $t9, 0($t1)\n");
                } else {
                    fprintf(out, "    sll $t0, $t0, 2\n");
                    fprintf(out, "    la $t1, %s\n", sym->name);
                    fprintf(out, "    add $t1, $t1, $t0\n");
                    fprintf(out, "    sw $t9, 0($t1)\n");
                }
            }
            else if (strcmp(arrayAccess->type, "array2d_access") == 0) {
                genExprMips(arrayAccess->left, out);
                fprintf(out, "    move $t2, $t0\n");
                fprintf(out, "    li $t3, %d\n", sym->dim2);
                fprintf(out, "    mul $t2, $t2, $t3\n");
                
                genExprMips(arrayAccess->right, out);
                fprintf(out, "    add $t0, $t2, $t0\n");
                
                if (sym->type == 'c') {
                    fprintf(out, "    la $t1, %s\n", sym->name);
                    fprintf(out, "    add $t1, $t1, $t0\n");
                    fprintf(out, "    sb $t9, 0($t1)\n");
                } else {
                    fprintf(out, "    sll $t0, $t0, 2\n");
                    fprintf(out, "    la $t1, %s\n", sym->name);
                    fprintf(out, "    add $t1, $t1, $t0\n");
                    fprintf(out, "    sw $t9, 0($t1)\n");
                }
            }
        }
        else if (strcmp(p->type, "print") == 0) {
            // Check if printing a string variable
            if (p->left && strcmp(p->left->type, "var") == 0) {
                Symbol* sym = lookupSymbol(p->left->name);
                if (sym && sym->stringValue) {
                    fprintf(out, "    la $a0, %s\n", sym->name);
                    fprintf(out, "    li $v0, 4\n    syscall\n");
                    fprintf(out, "    li $a0, 10\n    li $v0, 11\n    syscall\n");
                    p = p->next;
                    continue;
                }
            }
            
            genExprMips(p->left, out);
            
            if (p->left && strcmp(p->left->type, "var") == 0) {
                Symbol* sym = lookupSymbol(p->left->name);
                if (sym && sym->type == 'c') {
                    fprintf(out, "    move $a0, $t0\n    li $v0, 11\n    syscall\n");
                } else {
                    fprintf(out, "    move $a0, $t0\n    li $v0, 1\n    syscall\n");
                }
            }
            else if (p->left && strcmp(p->left->type, "char") == 0) {
                fprintf(out, "    move $a0, $t0\n    li $v0, 11\n    syscall\n");
            }
            else if (p->left && (strcmp(p->left->type, "array_access") == 0 || strcmp(p->left->type, "array2d_access") == 0)) {
                Symbol* sym = lookupSymbol(p->left->name);
                if (sym && sym->type == 'c') {
                    fprintf(out, "    move $a0, $t0\n    li $v0, 11\n    syscall\n");
                } else {
                    fprintf(out, "    move $a0, $t0\n    li $v0, 1\n    syscall\n");
                }
            }
            else {
                fprintf(out, "    move $a0, $t0\n    li $v0, 1\n    syscall\n");
            }
            
            fprintf(out, "    li $a0, 10\n    li $v0, 11\n    syscall\n");
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

    fprintf(out, ".data\n");

    for (int i = 0; i < symtab.count; i++) {
        Symbol* s = &symtab.vars[i];
        if (s->stringValue) {
            fprintf(out, "%s: .asciiz \"%s\"\n", s->name, s->stringValue);
        }
        else if (s->type == 'c') {
            if (s->dimensions == 0) {
                fprintf(out, "%s: .byte %d\n", s->name, s->initial_value);
            } else {
                fprintf(out, "%s: .space %d\n", s->name, s->size);
            }
        }
    }
    
    fprintf(out, ".align 2\n");
    
    for (int i = 0; i < symtab.count; i++) {
        Symbol* s = &symtab.vars[i];
        if (s->type == 'i') {
            if (s->dimensions == 0) {
                fprintf(out, "%s: .word %d\n", s->name, s->initial_value);
            } else {
                fprintf(out, "%s: .space %d\n", s->name, s->size * 4);
            }
        }
    }

    fprintf(out, ".text\n.globl main\nmain:\n");
    genStmtMips(root, out);
    fprintf(out, "    li $v0, 10\n    syscall\n");
    fclose(out);
}
