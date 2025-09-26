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
    else if (strcmp(node->type, "char") == 0) {
        char buf[16];
        sprintf(buf, "%d", node->value);  // Store as ASCII value
        *place = newTemp();
        return makeTAC(TAC_CHAR, *place, buf, NULL);
    }
    else if (strcmp(node->type, "var") == 0) {
        *place = strdup(node->name);
        return NULL;
    }
    else if (strcmp(node->type, "array_access") == 0) {
        char* indexPlace;
        TAC* indexCode = genExprTac(node->left, &indexPlace);
        *place = newTemp();
        TAC* accessCode = makeTAC(TAC_ARRAY_ACCESS, *place, node->name, indexPlace);
        return concat(indexCode, accessCode);
    }
    else if (strcmp(node->type, "array2d_access") == 0) {
        char* index1Place, *index2Place;
        TAC* index1Code = genExprTac(node->left, &index1Place);
        TAC* index2Code = genExprTac(node->right, &index2Place);
        *place = newTemp();
        
        // For 2D access, we need both indices - we'll use a special format
        char indexBuf[64];
        sprintf(indexBuf, "%s,%s", index1Place, index2Place);
        TAC* accessCode = makeTAC(TAC_ARRAY2D_ACCESS, *place, node->name, indexBuf);
        return concat(concat(index1Code, index2Code), accessCode);
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
    else if (strcmp(node->type, "array_assign") == 0) {
        ASTNode* arrayAccess = node->left;
        char* valuePlace;
        TAC* valueCode = genExprTac(node->right, &valuePlace);
        
        if (strcmp(arrayAccess->type, "array_access") == 0) {
            char* indexPlace;
            TAC* indexCode = genExprTac(arrayAccess->left, &indexPlace);
            TAC* assignCode = makeTAC(TAC_ARRAY_ASSIGN, arrayAccess->name, indexPlace, valuePlace);
            return concat(concat(indexCode, valueCode), assignCode);
        }
        else if (strcmp(arrayAccess->type, "array2d_access") == 0) {
            char* index1Place, *index2Place;
            TAC* index1Code = genExprTac(arrayAccess->left, &index1Place);
            TAC* index2Code = genExprTac(arrayAccess->right, &index2Place);
            
            char indexBuf[64];
            sprintf(indexBuf, "%s,%s", index1Place, index2Place);
            TAC* assignCode = makeTAC(TAC_ARRAY2D_ASSIGN, arrayAccess->name, indexBuf, valuePlace);
            return concat(concat(concat(index1Code, index2Code), valueCode), assignCode);
        }
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
    
    TAC* code = genStmtTac(root);
    if (root->next) {
        code = concat(code, genTAC(root->next));
    }
    
    return code;
}

/* Output TAC to file */
void generateTAC(ASTNode* root, const char* filename) {
    TAC* code = genTAC(root);
    FILE* out = fopen(filename, "w");
    if (!out) {
        perror(filename);
        return;
    }

    fprintf(out, "# Three Address Code\n");
    fprintf(out, "# Generated from AST\n\n");

    TAC* cur = code;
    while (cur) {
        switch (cur->op) {
            case TAC_ADD: 
                fprintf(out, "%s = %s + %s\n", cur->res, cur->arg1, cur->arg2); 
                break;
            case TAC_SUB: 
                fprintf(out, "%s = %s - %s\n", cur->res, cur->arg1, cur->arg2); 
                break;
            case TAC_MUL: 
                fprintf(out, "%s = %s * %s\n", cur->res, cur->arg1, cur->arg2); 
                break;
            case TAC_DIV: 
                fprintf(out, "%s = %s / %s\n", cur->res, cur->arg1, cur->arg2); 
                break;
            case TAC_ASSIGN: 
                fprintf(out, "%s = %s\n", cur->res, cur->arg1); 
                break;
            case TAC_VAR: 
                fprintf(out, "declare %s\n", cur->res); 
                break;
            case TAC_NUM: 
                fprintf(out, "%s = %s\n", cur->res, cur->arg1); 
                break;
            case TAC_CHAR: 
                fprintf(out, "%s = '%c'  // ASCII %s\n", cur->res, atoi(cur->arg1), cur->arg1); 
                break;
            case TAC_PRINT: 
                fprintf(out, "print %s\n", cur->arg1); 
                break;
            case TAC_ARRAY_DECL: 
                fprintf(out, "declare %s[%s]\n", cur->res, cur->arg1); 
                break;
            case TAC_ARRAY2D_DECL: 
                fprintf(out, "declare %s[%s][%s]\n", cur->res, cur->arg1, cur->arg2); 
                break;
            case TAC_ARRAY_ACCESS:
                fprintf(out, "%s = %s[%s]\n", cur->res, cur->arg1, cur->arg2);
                break;
            case TAC_ARRAY2D_ACCESS:
                fprintf(out, "%s = %s[%s]\n", cur->res, cur->arg1, cur->arg2);
                break;
            case TAC_ARRAY_ASSIGN:
                fprintf(out, "%s[%s] = %s\n", cur->res, cur->arg1, cur->arg2);
                break;
            case TAC_ARRAY2D_ASSIGN:
                fprintf(out, "%s[%s] = %s\n", cur->res, cur->arg1, cur->arg2);
                break;
        }
        cur = cur->next;
    }

    fclose(out);
    printf("TAC generated successfully: %s\n", filename);
}