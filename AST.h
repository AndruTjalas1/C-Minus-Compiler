#ifndef AST_H
#define AST_H

typedef struct ASTNode {
    char* type;              // e.g. "num", "var", "binop", "decl"
    char* name;              // for identifiers
    int value;               // for numbers or array size
    char op;                 // for operators
    struct ASTNode* left;    // left child
    struct ASTNode* right;   // right child
    struct ASTNode* next;    // for stmt lists
} ASTNode;

/* Constructors */
ASTNode* createStmtList(ASTNode* list, ASTNode* stmt);
ASTNode* createDecl(char* name);
ASTNode* createAssign(char* name, ASTNode* expr);
ASTNode* createNum(int value);
ASTNode* createVar(char* name);
ASTNode* createBinOp(char op, ASTNode* left, ASTNode* right);
ASTNode* createArrayDecl(char* name, int size);
ASTNode* create2DArrayDecl(char* name, int size1, int size2);

/* Debugging */
void printAST(ASTNode* node, int indent);

#endif
