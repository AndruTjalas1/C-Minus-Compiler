#include <stdio.h>
#include <string.h>
#include "AST.h"
#include "symtab.h"

/* Forward declarations */
void genExprMips(ASTNode* node, FILE* out);
void genStmtMips(ASTNode* node, FILE* out);

/* Generate MIPS for expressions */
void genExprMips(ASTNode* node, FILE* out) {
    if (!node) return;

    if (strcmp(node->type, "num") == 0) {
        fprintf(out, "li $t0, %d\n", node->value);  // load immediate
    } 
    else if (strcmp(node->type, "var") == 0) {
        fprintf(out, "lw $t0, %s\n", node->name);   // load variable by label
    } 
    else if (strcmp(node->type, "binop") == 0) {
        genExprMips(node->left, out);
        fprintf(out, "move $t1, $t0\n");            // save left operand
        genExprMips(node->right, out);              // right operand in $t0
        switch (node->op) {
            case '+': fprintf(out, "add $t0, $t1, $t0\n"); break;
            case '-': fprintf(out, "sub $t0, $t1, $t0\n"); break;
            case '*': fprintf(out, "mul $t0, $t1, $t0\n"); break;
            case '/': fprintf(out, "div $t1, $t0\nmflo $t0\n"); break;
        }
    }
}

/* Generate MIPS for statements */
void genStmtMips(ASTNode* node, FILE* out) {
    ASTNode* p = node;
    while (p) {
        if (strcmp(p->type, "assign") == 0) {
            genExprMips(p->left, out);
            fprintf(out, "sw $t0, %s\n", p->name);    // store result to variable label
        }
        else if (strcmp(p->type, "print") == 0) {
            genExprMips(p->left, out);
            fprintf(out, "move $a0, $t0\nli $v0, 1\nsyscall\n"); // print integer
            fprintf(out, "li $a0, 10\nli $v0, 11\nsyscall\n");    // newline
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
        if (s->size == 1)
            fprintf(out, "%s: .word 0\n", s->name);
        else
            fprintf(out, "%s: .space %d\n", s->name, s->size * 4);
    }

    /* Text section */
    fprintf(out, ".text\n.globl main\nmain:\n");

    /* Generate code for all statements */
    genStmtMips(root, out);

    fprintf(out, "li $v0, 10\nsyscall\n"); // exit
    fclose(out);
}
