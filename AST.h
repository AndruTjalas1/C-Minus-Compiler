#ifndef AST_H
#define AST_H

typedef struct ASTNode {
    char* type;              // e.g. "num", "var", "binop", "decl", "char", "array_access", "array_assign"
    char* name;              // for identifiers
    int value;               // for numbers, characters (as ASCII), or array size
    char op;                 // for operators
    struct ASTNode* left;    // left child
    struct ASTNode* right;   // right child
    struct ASTNode* next;    // for stmt lists
    struct ASTNode* index;   // for array index (used for 2D arrays)
} ASTNode;

/* Constructors */
ASTNode* createStmtList(ASTNode* list, ASTNode* stmt);
ASTNode* createDecl(char* name);
ASTNode* createAssign(char* name, ASTNode* expr);
ASTNode* createPrint(ASTNode* expr);
ASTNode* createNum(int value);
ASTNode* createChar(char c);
ASTNode* createVar(char* name);
ASTNode* createBinOp(char op, ASTNode* left, ASTNode* right);
ASTNode* createArrayDecl(char* name, int size);
ASTNode* create2DArrayDecl(char* name, int size1, int size2);

/* Array access and assignment */
ASTNode* createArrayAccess(char* name, ASTNode* index);
ASTNode* create2DArrayAccess(char* name, ASTNode* index1, ASTNode* index2);
ASTNode* createArrayAssign(ASTNode* arrayAccess, ASTNode* expr);

/* Debugging */
//void printAST(ASTNode* node, int indent);

#endif