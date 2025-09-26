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
    node->left = node->right = node->next = node->index = NULL;
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

ASTNode* createChar(char c) {
    ASTNode* node = newNode("char");
    node->value = (int)c;  // Store character as ASCII value
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

ASTNode* createArrayAccess(char* name, ASTNode* index) {
    ASTNode* node = newNode("array_access");
    node->name = strdup(name);
    node->left = index;  // store index expression
    return node;
}

ASTNode* create2DArrayAccess(char* name, ASTNode* index1, ASTNode* index2) {
    ASTNode* node = newNode("array2d_access");
    node->name = strdup(name);
    node->left = index1;   // first dimension index
    node->right = index2;  // second dimension index
    return node;
}

ASTNode* createArrayAssign(ASTNode* arrayAccess, ASTNode* expr) {
    ASTNode* node = newNode("array_assign");
    node->left = arrayAccess;  // the array access node
    node->right = expr;        // the expression to assign
    return node;
}