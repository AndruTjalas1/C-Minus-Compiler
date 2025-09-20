#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

static ASTNode* newNode(const char* type) {
    ASTNode* node = malloc(sizeof(ASTNode));
    node->type = strdup(type);
    node->name = NULL;
    node->value = 0;
    node->op = 0;
    node->left = node->right = node->next = NULL;
    return node;
}

ASTNode* createStmtList(ASTNode* list, ASTNode* stmt) {
    if (!list) return stmt;
    ASTNode* p = list;
    while (p->next) p = p->next;
    p->next = stmt;
    return list;
}

ASTNode* createDecl(char* name) {
    ASTNode* node = newNode("decl");
    node->name = strdup(name);
    return node;
}

ASTNode* createAssign(char* name, ASTNode* expr) {
    ASTNode* node = newNode("assign");
    node->name = strdup(name);
    node->left = expr;
    return node;
}

ASTNode* createNum(int value) {
    ASTNode* node = newNode("num");
    node->value = value;
    return node;
}

ASTNode* createVar(char* name) {
    ASTNode* node = newNode("var");
    node->name = strdup(name);
    return node;
}

ASTNode* createBinOp(char op, ASTNode* left, ASTNode* right) {
    ASTNode* node = newNode("binop");
    node->op = op;
    node->left = left;
    node->right = right;
    return node;
}

ASTNode* createArrayDecl(char* name, int size) {
    ASTNode* node = newNode("array_decl");
    node->name = strdup(name);
    node->value = size;   // store array size
    return node;
}

ASTNode* create2DArrayDecl(char* name, int size1, int size2) {
    ASTNode* node = newNode("array2d_decl");
    node->name = strdup(name);
    node->left = createNum(size1);   // store first dimension
    node->right = createNum(size2);  // store second dimension
    return node;
}

ASTNode* createPrint(ASTNode* expr) {
    ASTNode* node = newNode("print");
    node->left = expr;   // expression to print
    return node;
}

/*void printAST(ASTNode* node, int indent) {
    if (!node) return;
    for (int i = 0; i < indent; i++) printf("  ");

    if (strcmp(node->type, "num") == 0) {
        printf("Num(%d)\n", node->value);
    } else if (strcmp(node->type, "var") == 0) {
        printf("Var(%s)\n", node->name);
    } else if (strcmp(node->type, "decl") == 0) {
        printf("Decl(%s)\n", node->name);
    } else if (strcmp(node->type, "assign") == 0) {
        printf("Assign(%s)\n", node->name);
        printAST(node->left, indent + 1);
    } else if (strcmp(node->type, "binop") == 0) {
        printf("BinOp(%c)\n", node->op);
        printAST(node->left, indent + 1);
        printAST(node->right, indent + 1);
    } else if (strcmp(node->type, "array_decl") == 0) {
        printf("ArrayDecl(%s, size=%d)\n", node->name, node->value);
    } else if (strcmp(node->type, "array2d_decl") == 0) {
        printf("Array2DDecl(%s)\n", node->name);
        printAST(node->left, indent + 1);   // print first dimension
        printAST(node->right, indent + 1);  // print second dimension
    } else if (strcmp(node->type, "print") == 0) {
        printf("Print\n");
        printAST(node->left, indent + 1);
    }

    printAST(node->next, indent);
}*/
