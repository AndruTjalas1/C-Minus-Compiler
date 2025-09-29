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
    else if (strcmp(node->type, "array_access") == 0) {
        Symbol* sym = lookupSymbol(node->name);
        if (!sym) {
            fprintf(stderr, "Error: undeclared array '%s'\n", node->name);
            return;
        }
        
        // Generate code for index expression
        genExprMips(node->left, out);  // index in $t0
        
        // Calculate address: base + (index * element_size)
        if (sym->type == 'c') {
            // For char arrays: address = base + index
            fprintf(out, "    la $t1, %s\n", sym->name);     // load base address
            fprintf(out, "    add $t1, $t1, $t0\n");         // add index
            fprintf(out, "    lb $t0, 0($t1)\n");            // load byte from address
        } else {
            // For int arrays: address = base + (index * 4)
            fprintf(out, "    sll $t0, $t0, 2\n");           // multiply index by 4
            fprintf(out, "    la $t1, %s\n", sym->name);     // load base address
            fprintf(out, "    add $t1, $t1, $t0\n");         // add offset
            fprintf(out, "    lw $t0, 0($t1)\n");            // load word from address
        }
    }
    else if (strcmp(node->type, "array2d_access") == 0) {
        Symbol* sym = lookupSymbol(node->name);
        if (!sym) {
            fprintf(stderr, "Error: undeclared array '%s'\n", node->name);
            return;
        }
        
        // Calculate 2D array offset: (row * col_size + col) * element_size
        genExprMips(node->left, out);    // row index in $t0
        fprintf(out, "    move $t2, $t0\n");              // save row index
        fprintf(out, "    li $t3, %d\n", sym->dim2);      // column size
        fprintf(out, "    mul $t2, $t2, $t3\n");          // row * col_size
        
        genExprMips(node->right, out);   // col index in $t0
        fprintf(out, "    add $t0, $t2, $t0\n");          // row*col_size + col
        
        if (sym->type == 'c') {
            fprintf(out, "    la $t1, %s\n", sym->name);   // load base address
            fprintf(out, "    add $t1, $t1, $t0\n");       // add offset
            fprintf(out, "    lb $t0, 0($t1)\n");          // load byte
        } else {
            fprintf(out, "    sll $t0, $t0, 2\n");         // multiply by 4
            fprintf(out, "    la $t1, %s\n", sym->name);   // load base address
            fprintf(out, "    add $t1, $t1, $t0\n");       // add offset
            fprintf(out, "    lw $t0, 0($t1)\n");          // load word
        }
    } 
    else if (strcmp(node->type, "binop") == 0) {
        // Save $s0 before using it
        fprintf(out, "    sw $s0, -4($sp)\n");    // preserve $s0
        fprintf(out, "    addiu $sp, $sp, -4\n"); // adjust stack

        genExprMips(node->left, out);
        fprintf(out, "    move $s0, $t0\n");      // save left operand in $s0
        genExprMips(node->right, out);            // right operand in $t0
        switch (node->op) {
            case '+': fprintf(out, "    add $t0, $s0, $t0\n"); break;
            case '-': fprintf(out, "    sub $t0, $s0, $t0\n"); break;
            case '*': fprintf(out, "    mul $t0, $s0, $t0\n"); break;
            case '/': fprintf(out, "    div $s0, $t0\n    mflo $t0\n"); break;
        }

        // Restore $s0
        fprintf(out, "    addiu $sp, $sp, 4\n");  // restore stack
        fprintf(out, "    lw $s0, -4($sp)\n");    // restore $s0
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
        else if (strcmp(p->type, "array_decl_init") == 0) {
            // Handle initialized array - generate assignments
            Symbol* sym = lookupSymbol(p->name);
            if (!sym || !sym->initValues) {
                p = p->next;
                continue;
            }
            
            // Generate assignments for each initialized value
            for (int i = 0; i < sym->initCount && i < sym->dim1; i++) {
                fprintf(out, "    li $t0, %d\n", sym->initValues[i]);
                fprintf(out, "    li $t1, %d\n", i);  // index
                
                if (sym->type == 'c') {
                    fprintf(out, "    la $t2, %s\n", sym->name);     // base address
                    fprintf(out, "    add $t2, $t2, $t1\n");         // add index
                    fprintf(out, "    sb $t0, 0($t2)\n");            // store byte
                } else {
                    fprintf(out, "    sll $t1, $t1, 2\n");           // multiply by 4
                    fprintf(out, "    la $t2, %s\n", sym->name);     // base address
                    fprintf(out, "    add $t2, $t2, $t1\n");         // add offset
                    fprintf(out, "    sw $t0, 0($t2)\n");            // store word
                }
            }
        }
        else if (strcmp(p->type, "array_assign") == 0) {
            // Generate code for the value to assign
            genExprMips(p->right, out);  // value in $t0
            fprintf(out, "    move $t9, $t0\n");  // save value
            
            ASTNode* arrayAccess = p->left;
            Symbol* sym = lookupSymbol(arrayAccess->name);
            if (!sym) {
                fprintf(stderr, "Error: undeclared array '%s'\n", arrayAccess->name);
                return;
            }
            
            if (strcmp(arrayAccess->type, "array_access") == 0) {
                // 1D array assignment
                genExprMips(arrayAccess->left, out);  // index in $t0
                
                if (sym->type == 'c') {
                    fprintf(out, "    la $t1, %s\n", sym->name);     // base address
                    fprintf(out, "    add $t1, $t1, $t0\n");         // add index
                    fprintf(out, "    sb $t9, 0($t1)\n");            // store byte
                } else {
                    fprintf(out, "    sll $t0, $t0, 2\n");           // multiply by 4
                    fprintf(out, "    la $t1, %s\n", sym->name);     // base address
                    fprintf(out, "    add $t1, $t1, $t0\n");         // add offset
                    fprintf(out, "    sw $t9, 0($t1)\n");            // store word
                }
            }
            else if (strcmp(arrayAccess->type, "array2d_access") == 0) {
                // 2D array assignment
                genExprMips(arrayAccess->left, out);    // row index in $t0
                fprintf(out, "    move $t2, $t0\n");              // save row
                fprintf(out, "    li $t3, %d\n", sym->dim2);      // column size
                fprintf(out, "    mul $t2, $t2, $t3\n");          // row * col_size
                
                genExprMips(arrayAccess->right, out);   // col index in $t0
                fprintf(out, "    add $t0, $t2, $t0\n");          // total offset
                
                if (sym->type == 'c') {
                    fprintf(out, "    la $t1, %s\n", sym->name);   // base address
                    fprintf(out, "    add $t1, $t1, $t0\n");       // add offset
                    fprintf(out, "    sb $t9, 0($t1)\n");          // store byte
                } else {
                    fprintf(out, "    sll $t0, $t0, 2\n");         // multiply by 4
                    fprintf(out, "    la $t1, %s\n", sym->name);   // base address
                    fprintf(out, "    add $t1, $t1, $t0\n");       // add offset
                    fprintf(out, "    sw $t9, 0($t1)\n");          // store word
                }
            }
        }
        else if (strcmp(p->type, "print") == 0) {
            genExprMips(p->left, out);
            
            // Determine what type we're printing
            if (p->left && strcmp(p->left->type, "var") == 0) {
                Symbol* sym = lookupSymbol(p->left->name);
                if (sym && sym->type == 'c') {
                    fprintf(out, "    move $a0, $t0\n    li $v0, 11\n    syscall\n"); // print char
                } else {
                    fprintf(out, "    move $a0, $t0\n    li $v0, 1\n    syscall\n");  // print int
                }
            }
            else if (p->left && strcmp(p->left->type, "char") == 0) {
                fprintf(out, "    move $a0, $t0\n    li $v0, 11\n    syscall\n"); // print char
            }
            else if (p->left && (strcmp(p->left->type, "array_access") == 0 || strcmp(p->left->type, "array2d_access") == 0)) {
                // For array access, check the array type
                Symbol* sym = lookupSymbol(p->left->name);
                if (sym && sym->type == 'c') {
                    fprintf(out, "    move $a0, $t0\n    li $v0, 11\n    syscall\n"); // print char
                } else {
                    fprintf(out, "    move $a0, $t0\n    li $v0, 1\n    syscall\n");  // print int
                }
            }
            else {
                fprintf(out, "    move $a0, $t0\n    li $v0, 1\n    syscall\n");  // default to int
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
    
    // First pass: declare all char variables and arrays
    for (int i = 0; i < symtab.count; i++) {
        Symbol* s = &symtab.vars[i];
        if (s->type == 'c') {
            if (s->dimensions == 0) {
                // Scalar char variable
                fprintf(out, "%s: .byte %d\n", s->name, s->initial_value);
            } else {
                // Char array - allocate space
                fprintf(out, "%s: .space %d\n", s->name, s->size);
            }
        }
    }
    
    // Add alignment for integer data
    fprintf(out, ".align 2\n");
    
    // Second pass: declare all int variables and arrays
    for (int i = 0; i < symtab.count; i++) {
        Symbol* s = &symtab.vars[i];
        if (s->type == 'i') {
            if (s->dimensions == 0) {
                // Scalar int variable
                fprintf(out, "%s: .word %d\n", s->name, s->initial_value);
            } else {
                // Int array - allocate space (aligned)
                fprintf(out, "%s: .space %d\n", s->name, s->size * 4);
            }
        }
    }

    /* Text section */
    fprintf(out, ".text\n.globl main\nmain:\n");

    /* Generate code for all statements */
    genStmtMips(root, out);

    fprintf(out, "    li $v0, 10\n    syscall\n"); // exit
    fclose(out);
}