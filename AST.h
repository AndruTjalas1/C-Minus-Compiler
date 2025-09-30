#ifndef AST_H
#define AST_H

typedef struct ASTNode {
    char* type;
    char* name;
    int value;
    char op;
    struct ASTNode* left;
    struct ASTNode* right;
    struct ASTNode* next;
    struct ASTNode* index;
} ASTNode;

ASTNode* createStmtList(ASTNode* list, ASTNode* stmt);
ASTNode* createDecl(char* name);
ASTNode* createAssign(char* name, ASTNode* expr);
ASTNode* createPrint(ASTNode* expr);
ASTNode* createNum(int value);
ASTNode* createChar(char c);
ASTNode* createStringDecl(char* name, char* value);
ASTNode* createVar(char* name);
ASTNode* createBinOp(char op, ASTNode* left, ASTNode* right);
ASTNode* createArrayDecl(char* name, int size);
ASTNode* create2DArrayDecl(char* name, int size1, int size2);
ASTNode* createArrayAccess(char* name, ASTNode* index);
ASTNode* create2DArrayAccess(char* name, ASTNode* index1, ASTNode* index2);
ASTNode* createArrayAssign(ASTNode* arrayAccess, ASTNode* expr);
ASTNode* createArrayDeclInit(char* name, int size, ASTNode* initList);
ASTNode* create2DArrayDeclInit(char* name, int size1, int size2, ASTNode* initList);
ASTNode* createInitList(ASTNode* list, ASTNode* expr);

#endif