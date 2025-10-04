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
    struct ASTNode* condition;
    struct ASTNode* ifBlock;
    struct ASTNode* elseifList;
    struct ASTNode* elseBlock;
    struct ASTNode* loopInit;
    struct ASTNode* loopUpdate;
    struct ASTNode* loopBody;
} ASTNode;

// Memory pool functions
void init_ast_memory();
void* ast_alloc(size_t size);
void print_ast_memory_stats();
void free_ast_memory();

// AST node creation functions
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
ASTNode* createCondition(char* op, ASTNode* left, ASTNode* right);
ASTNode* createIf(ASTNode* condition, ASTNode* ifBlock, ASTNode* elseifList, ASTNode* elseBlock);
ASTNode* createElseIf(ASTNode* condition, ASTNode* block);
ASTNode* createElseIfList(ASTNode* list, ASTNode* condition, ASTNode* block);
ASTNode* createFor(ASTNode* init, ASTNode* condition, ASTNode* update, ASTNode* body);
ASTNode* createWhile(ASTNode* condition, ASTNode* body);
ASTNode* createDoWhile(ASTNode* condition, ASTNode* body);

#endif
