#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tac.h"
#include "AST.h"

static int tempCount = 0;

/* Generate a new temporary variable name */
char* newTemp() {
    char* buf = malloc(16);
    sprintf(buf, "t%d", tempCount++);
    return buf;
}

/* Make TAC instruction */
TAC* makeTAC(TACOp op, char* res, char* arg1, char* arg2) {
    TAC* tac = malloc(sizeof(TAC));
    tac->op = op;
    tac->res = res ? strdup(res) : NULL;
    tac->arg1 = arg1 ? strdup(arg1) : NULL;
    tac->arg2 = arg2 ? strdup(arg2) : NULL;
    tac->next = NULL;
    return tac;
}

/* Concatenate two TAC lists */
TAC* concat(TAC* code1, TAC* code2) {
    if (!code1) return code2;
    TAC* cur = code1;
    while (cur->next) cur = cur->next;
    cur->next = code2;
    return code1;
}

/* Generate TAC for expressions */
TAC* genExprTac(ASTNode* node, char** place) {
    if (!node) return NULL;

    if (strcmp(node->type, "num") == 0) {
        char buf[16];
        sprintf(buf, "%d", node->value);
        *place = newTemp();
        return makeTAC(TAC_NUM, *place, buf, NULL);
    }
    else if (strcmp(node->type, "var") == 0) {
        *place = node->name;
        return NULL;
    }
    else if (strcmp(node->type, "binop") == 0) {
        char* t1; char* t2;
        TAC* c1 = genExprTac(node->left, &t1);
        TAC* c2 = genExprTac(node->right, &t2);
        *place = newTemp();
        TACOp op;
        switch (node->op) {
            case '+': op = TAC_ADD; break;
            case '-': op = TAC_SUB; break;
            case '*': op = TAC_MUL; break;
            case '/': op = TAC_DIV; break;
            default: op = TAC_ADD; break;
        }
        return concat(concat(c1, c2), makeTAC(op, *place, t1, t2));
    }

    return NULL;
}

/* Generate TAC for statements */
TAC* genStmtTac(ASTNode* node) {
    if (!node) return NULL;

    if (strcmp(node->type, "assign") == 0) {
        char* t1;
        TAC* c1 = genExprTac(node->left, &t1);
        TAC* assign = makeTAC(TAC_ASSIGN, node->name, t1, NULL);
        return concat(c1, assign);
    }
    else if (strcmp(node->type, "print") == 0) {
        char* t1;
        TAC* c1 = genExprTac(node->left, &t1);
        TAC* p = makeTAC(TAC_PRINT, NULL, t1, NULL);
        return concat(c1, p);
    }
    else if (strcmp(node->type, "decl") == 0) {
        return makeTAC(TAC_VAR, node->name, NULL, NULL);
    }
    else if (strcmp(node->type, "array_decl") == 0) {
        char buf[16];
        sprintf(buf, "%d", node->value);
        return makeTAC(TAC_ARRAY_DECL, node->name, buf, NULL);
    }
    else if (strcmp(node->type, "array2d_decl") == 0) {
        char buf1[16], buf2[16];
        sprintf(buf1, "%d", node->left->value);
        sprintf(buf2, "%d", node->right->value);
        return makeTAC(TAC_ARRAY2D_DECL, node->name, buf1, buf2);
    }

    return NULL;
}

/* Generate TAC recursively for AST */
TAC* genTAC(ASTNode* root) {
    if (!root) return NULL;
    TAC* code = NULL;
    if (strcmp(root->type, "stmt_list") == 0) {
        code = concat(genTAC(root->left), genTAC(root->right));
    } else {
        code = genStmtTac(root);
    }
    return code;
}

/* Output TAC to file */
void generateTAC(ASTNode* root, const char* filename) {
    TAC* code = genTAC(root);
    FILE* out = fopen(filename, "w");
    if (!out) {
        perror(filename);
        exit(1);
    }

    TAC* cur = code;
    while (cur) {
        switch (cur->op) {
            case TAC_ADD: fprintf(out, "%s = %s + %s\n", cur->res, cur->arg1, cur->arg2); break;
            case TAC_SUB: fprintf(out, "%s = %s - %s\n", cur->res, cur->arg1, cur->arg2); break;
            case TAC_MUL: fprintf(out, "%s = %s * %s\n", cur->res, cur->arg1, cur->arg2); break;
            case TAC_DIV: fprintf(out, "%s = %s / %s\n", cur->res, cur->arg1, cur->arg2); break;
            case TAC_ASSIGN: fprintf(out, "%s = %s\n", cur->res, cur->arg1); break;
            case TAC_VAR: fprintf(out, "declare %s\n", cur->res); break;
            case TAC_NUM: fprintf(out, "%s = %s\n", cur->res, cur->arg1); break;
            case TAC_PRINT: fprintf(out, "print %s\n", cur->arg1); break;
            case TAC_ARRAY_DECL: fprintf(out, "declare %s[%s]\n", cur->res, cur->arg1); break;
            case TAC_ARRAY2D_DECL: fprintf(out, "declare %s[%s][%s]\n", cur->res, cur->arg1, cur->arg2); break;
        }
        cur = cur->next;
    }

    fclose(out);
}
