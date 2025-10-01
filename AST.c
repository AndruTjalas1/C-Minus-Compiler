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
    node->condition = node->ifBlock = node->elseifList = node->elseBlock = NULL;
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

ASTNode* createStringDecl(char* name, char* value) {
    ASTNode* node = newNode("string_decl");
    node->name = strdup(name);
    node->left = malloc(sizeof(ASTNode));
    node->left->type = strdup("string_literal");
    node->left->name = strdup(value);
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

ASTNode* createArrayDeclInit(char* name, int size, ASTNode* initList) {
    ASTNode* node = newNode("array_decl_init");
    node->name = strdup(name);
    node->value = size;        // array size
    node->left = initList;     // initialization list
    return node;
}

ASTNode* create2DArrayDeclInit(char* name, int size1, int size2, ASTNode* initList) {
    ASTNode* node = newNode("array2d_decl_init");
    node->name = strdup(name);
    node->left = createNum(size1);    // first dimension
    node->right = createNum(size2);   // second dimension
    node->index = initList;           // initialization list
    return node;
}

ASTNode* createInitList(ASTNode* list, ASTNode* expr) {
    if (!list) return expr;
    ASTNode* p = list;
    while (p->next) p = p->next;
    p->next = expr;
    return list;
}

ASTNode* createCondition(char* op, ASTNode* left, ASTNode* right) {
    ASTNode* node = newNode("condition");
    node->name = strdup(op);  // store operator as name
    node->left = left;
    node->right = right;
    return node;
}

ASTNode* createIf(ASTNode* condition, ASTNode* ifBlock, ASTNode* elseifList, ASTNode* elseBlock) {
    ASTNode* node = newNode("if");
    node->condition = condition;
    node->ifBlock = ifBlock;
    node->elseifList = elseifList;
    node->elseBlock = elseBlock;
    return node;
}

ASTNode* createElseIf(ASTNode* condition, ASTNode* block) {
    ASTNode* node = newNode("elseif");
    node->condition = condition;
    node->ifBlock = block;
    return node;
}

ASTNode* createElseIfList(ASTNode* list, ASTNode* condition, ASTNode* block) {
    ASTNode* elseifNode = createElseIf(condition, block);
    if (!list) return elseifNode;
    ASTNode* p = list;
    while (p->next) p = p->next;
    p->next = elseifNode;
    return list;
}