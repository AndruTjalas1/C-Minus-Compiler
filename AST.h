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
    // Function-related fields
    char* returnType;
    struct ASTNode* params;
    struct ASTNode* body;
    struct ASTNode* args;
    // Array parameter fields
    int isArrayParam;         // 1 if this parameter is an array
    int arrayDim1;            // First dimension (0 if variable-length [])
    int arrayDim2;            // Second dimension (0 if not applicable)
    // Switch-case fields
    struct ASTNode* switchExpr;
    struct ASTNode* cases;
    struct ASTNode* caseValue;
    struct ASTNode* caseBody;
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
ASTNode* createPrintln(ASTNode* expr);
ASTNode* createNum(int value);
ASTNode* createChar(char c);
ASTNode* createBool(int value);
ASTNode* createStringLiteral(char* value);
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
ASTNode* createSwitch(ASTNode* expr, ASTNode* cases);
ASTNode* createCase(ASTNode* value, ASTNode* body);
ASTNode* createDefaultCase(ASTNode* body);
ASTNode* createCaseList(ASTNode* list, ASTNode* caseNode);
ASTNode* createBreak();
ASTNode* createContinue();

// Function-related node creation
ASTNode* createFunctionDecl(char* returnType, char* name, ASTNode* params, ASTNode* body);
ASTNode* createParam(char* type, char* name);
ASTNode* createArrayParam(char* type, char* name, int dim1, int dim2);
ASTNode* createParamList(ASTNode* list, ASTNode* param);
ASTNode* createFunctionCall(char* name, ASTNode* args);
ASTNode* createArgList(ASTNode* list, ASTNode* arg);
ASTNode* createReturn(ASTNode* expr);

#endif
