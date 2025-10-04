#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "stringpool.h"

/* ========== MEMORY POOL FOR AST NODES ========== */

#define POOL_SIZE 4096  // Allocate in 4KB chunks
#define MAX_POOLS 100

typedef struct MemPool {
    char* memory;
    size_t used;
    size_t size;
    struct MemPool* next;
} MemPool;

typedef struct {
    MemPool* current;
    MemPool* head;
    int total_allocations;
    int pool_count;
    size_t total_memory;
} ASTMemoryManager;

static ASTMemoryManager ast_mem = {0};

// Initialize memory pool
void init_ast_memory() {
    if (ast_mem.head) return;  // Already initialized
    
    ast_mem.head = malloc(sizeof(MemPool));
    ast_mem.head->memory = malloc(POOL_SIZE);
    ast_mem.head->used = 0;
    ast_mem.head->size = POOL_SIZE;
    ast_mem.head->next = NULL;
    ast_mem.current = ast_mem.head;
    ast_mem.pool_count = 1;
    ast_mem.total_memory = POOL_SIZE;
}

// Allocate from pool
void* ast_alloc(size_t size) {
    // Initialize if needed
    if (!ast_mem.head) {
        init_ast_memory();
    }
    
    // Align to 8 bytes for better performance
    size = (size + 7) & ~7;

    if (ast_mem.current->used + size > ast_mem.current->size) {
        // Need new pool
        if (ast_mem.pool_count >= MAX_POOLS) {
            fprintf(stderr, "Error: AST memory pool limit reached\n");
            exit(1);
        }
        
        MemPool* new_pool = malloc(sizeof(MemPool));
        new_pool->memory = malloc(POOL_SIZE);
        new_pool->used = 0;
        new_pool->size = POOL_SIZE;
        new_pool->next = NULL;

        ast_mem.current->next = new_pool;
        ast_mem.current = new_pool;
        ast_mem.pool_count++;
        ast_mem.total_memory += POOL_SIZE;
    }

    void* ptr = ast_mem.current->memory + ast_mem.current->used;
    ast_mem.current->used += size;
    ast_mem.total_allocations++;

    return ptr;
}

// Print memory pool statistics
void print_ast_memory_stats() {
    printf("\n=== AST Memory Pool Statistics ===\n");
    printf("Total allocations: %d\n", ast_mem.total_allocations);
    printf("Number of pools: %d\n", ast_mem.pool_count);
    printf("Total memory allocated: %zu KB\n", ast_mem.total_memory / 1024);
    
    size_t used = 0;
    MemPool* pool = ast_mem.head;
    while (pool) {
        used += pool->used;
        pool = pool->next;
    }
    printf("Memory used: %zu KB (%.1f%%)\n", 
           used / 1024, 
           (double)used / ast_mem.total_memory * 100.0);
}

// Free all memory pools
void free_ast_memory() {
    MemPool* pool = ast_mem.head;
    while (pool) {
        MemPool* next = pool->next;
        free(pool->memory);
        free(pool);
        pool = next;
    }
    ast_mem.head = NULL;
    ast_mem.current = NULL;
    ast_mem.pool_count = 0;
    ast_mem.total_memory = 0;
    ast_mem.total_allocations = 0;
}

/* ========== AST NODE CREATION FUNCTIONS ========== */

static ASTNode* newNode(const char* type) {
    ASTNode* node = ast_alloc(sizeof(ASTNode));  // Use memory pool
    node->type = intern_string(type);  // Use string interning
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
    node->name = intern_string(name);
    return node;
}

ASTNode* createAssign(char* name, ASTNode* expr) {
    ASTNode* node = newNode("assign");
    node->name = intern_string(name);
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
    node->name = intern_string(name);
    node->left = ast_alloc(sizeof(ASTNode));
    node->left->type = intern_string("string_literal");
    node->left->name = intern_string(value);
    return node;
}

ASTNode* createVar(char* name) {
    ASTNode* node = newNode("var");
    node->name = intern_string(name);
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
    node->name = intern_string(name);
    node->value = size;   // store array size
    return node;
}

ASTNode* create2DArrayDecl(char* name, int size1, int size2) {
    ASTNode* node = newNode("array2d_decl");
    node->name = intern_string(name);
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
    node->name = intern_string(name);
    node->left = index;  // store index expression
    return node;
}

ASTNode* create2DArrayAccess(char* name, ASTNode* index1, ASTNode* index2) {
    ASTNode* node = newNode("array2d_access");
    node->name = intern_string(name);
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
    node->name = intern_string(name);
    node->value = size;        // array size
    node->left = initList;     // initialization list
    return node;
}

ASTNode* create2DArrayDeclInit(char* name, int size1, int size2, ASTNode* initList) {
    ASTNode* node = newNode("array2d_decl_init");
    node->name = intern_string(name);
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
    node->name = intern_string(op);  // store operator as name
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

ASTNode* createFor(ASTNode* init, ASTNode* condition, ASTNode* update, ASTNode* body) {
    ASTNode* node = newNode("for");
    node->loopInit = init;
    node->condition = condition;
    node->loopUpdate = update;
    node->loopBody = body;
    return node;
}

ASTNode* createWhile(ASTNode* condition, ASTNode* body) {
    ASTNode* node = newNode("while");
    node->condition = condition;
    node->loopBody = body;
    return node;
}

ASTNode* createDoWhile(ASTNode* condition, ASTNode* body) {
    ASTNode* node = newNode("do_while");
    node->condition = condition;
    node->loopBody = body;
    return node;
}
