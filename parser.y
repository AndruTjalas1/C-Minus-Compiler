%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "symtab.h"

extern int yylex();
extern FILE* yyin;

ASTNode* root = NULL;

void yyerror(const char* s);
int* extractInitValues(ASTNode* initList, int* count);
%}

%union {
    int num;
    char* str;
    char character;
    ASTNode* node;
}

%token <str> IDENTIFIER
%token <str> TYPE
%token <num> NUMBER
%token <character> CHAR_LITERAL
%token <str> STRING_LITERAL
%token SEMICOLON EQ PLUS MINUS MULTIPLY DIVIDE
%token LBRACKET RBRACKET LBRACE RBRACE COMMA KEYWORD
%token LPAREN RPAREN
%token IF ELSEIF ELSE
%token FOR WHILE DO
%token EQEQ NEQ LT LE GT GE
%token AND OR NOT XOR

%type <node> program stmt declaration assignment expression print_stmt
%type <node> array_access init_list if_stmt condition stmt_block elseif_list stmt_list
%type <node> for_stmt while_stmt do_while_stmt loop_init loop_update

%left OR
%left XOR
%left AND
%right NOT
%left EQEQ NEQ
%left LT LE GT GE
%left PLUS MINUS
%left MULTIPLY DIVIDE

%%

program:
      program stmt       { root = createStmtList(root, $2); $$ = root; }
    | /* empty */        { $$ = NULL; }
    ;

stmt:
      declaration
    | assignment
    | print_stmt
    | if_stmt
    | for_stmt
    | while_stmt
    | do_while_stmt
    ;

declaration:
      TYPE IDENTIFIER SEMICOLON
        { 
          $$ = createDecl($2);
          char varType;
          if (strcmp($1, "char") == 0) varType = 'c';
          else if (strcmp($1, "string") == 0) varType = 's';
          else varType = 'i';
          addVar($2, 1, 0, varType);
          printf("Variable declaration: %s\n", $2); 
        }
    | TYPE IDENTIFIER EQ expression SEMICOLON
        { 
          $$ = createAssign($2, $4);
          char varType;
          if (strcmp($1, "char") == 0) varType = 'c';
          else if (strcmp($1, "string") == 0) varType = 's';
          else varType = 'i';
          addVar($2, 1, $4->value, varType);
          printf("Initialized variable: %s\n", $2);
        }
    | TYPE IDENTIFIER LBRACKET NUMBER RBRACKET EQ LBRACE init_list RBRACE SEMICOLON
        { 
          int initCount;
          int* initValues = extractInitValues($8, &initCount);
          $$ = createArrayDeclInit($2, $4, $8);
          char varType = (strcmp($1, "char") == 0) ? 'c' : 'i';
          addArrayWithInit($2, $4, varType, initValues, initCount);
          printf("Initialized array declaration: %s[%d] with %d values\n", $2, $4, initCount);
        }
    | TYPE IDENTIFIER LBRACKET NUMBER RBRACKET SEMICOLON
        { 
          $$ = createArrayDecl($2, $4);
          char varType = (strcmp($1, "char") == 0) ? 'c' : 'i';
          addArray($2, $4, varType);
          printf("Array declaration: %s[%d]\n", $2, $4);
        }
    | TYPE IDENTIFIER LBRACKET NUMBER RBRACKET LBRACKET NUMBER RBRACKET SEMICOLON
        { 
          $$ = create2DArrayDecl($2, $4, $7);
          char varType = (strcmp($1, "char") == 0) ? 'c' : 'i';
          add2DArray($2, $4, $7, varType);
          printf("2D Array declaration: %s[%d][%d]\n", $2, $4, $7);
        }
    | TYPE IDENTIFIER LBRACKET NUMBER RBRACKET LBRACKET NUMBER RBRACKET EQ LBRACE init_list RBRACE SEMICOLON
        { 
          int initCount;
          int* initValues = extractInitValues($11, &initCount);
          $$ = create2DArrayDeclInit($2, $4, $7, $11);
          char varType = (strcmp($1, "char") == 0) ? 'c' : 'i';
          add2DArrayWithInit($2, $4, $7, varType, initValues, initCount);
          printf("Initialized 2D array declaration: %s[%d][%d] with %d values\n", $2, $4, $7, initCount);
        }
    | TYPE IDENTIFIER EQ STRING_LITERAL SEMICOLON
        {
            if (strcmp($1, "string") == 0) {
                $$ = createStringDecl($2, $4);
                addStringVar($2, $4);
                printf("String declaration: %s = \"%s\"\n", $2, $4);
            } else {
                fprintf(stderr, "Error: string literals must use 'string' type\n");
                exit(1);
            }
        }
    ;

assignment:
      IDENTIFIER EQ expression SEMICOLON
        { 
          if (!isVarDeclared($1)) {
              fprintf(stderr, "Error: variable '%s' not declared\n", $1);
              exit(1);
          }
          $$ = createAssign($1, $3); 
          printf("Assignment: %s\n", $1);
        }
    | array_access EQ expression SEMICOLON
        {
          $$ = createArrayAssign($1, $3);
          printf("Array assignment\n");
        }
    ;

print_stmt:
      KEYWORD LPAREN expression RPAREN SEMICOLON
        {
            $$ = createPrint($3);
            printf("Print statement created\n");
        }
    ;

array_access:
      IDENTIFIER LBRACKET expression RBRACKET
        {
          if (!isVarDeclared($1)) {
              fprintf(stderr, "Error: variable '%s' not declared\n", $1);
              exit(1);
          }
          $$ = createArrayAccess($1, $3);
        }
    | IDENTIFIER LBRACKET expression RBRACKET LBRACKET expression RBRACKET
        {
          if (!isVarDeclared($1)) {
              fprintf(stderr, "Error: variable '%s' not declared\n", $1);
              exit(1);
          }
          $$ = create2DArrayAccess($1, $3, $6);
        }
    ;

init_list:
      expression       { $$ = $1; }
    | init_list COMMA expression { $$ = createInitList($1, $3); }
    ;

if_stmt:
      IF LPAREN condition RPAREN stmt_block
        {
          $$ = createIf($3, $5, NULL, NULL);
          printf("If statement created\n");
        }
    | IF LPAREN condition RPAREN stmt_block ELSE stmt_block
        {
          $$ = createIf($3, $5, NULL, $7);
          printf("If-else statement created\n");
        }
    | IF LPAREN condition RPAREN stmt_block elseif_list
        {
          $$ = createIf($3, $5, $6, NULL);
          printf("If-elseif statement created\n");
        }
    | IF LPAREN condition RPAREN stmt_block elseif_list ELSE stmt_block
        {
          $$ = createIf($3, $5, $6, $8);
          printf("If-elseif-else statement created\n");
        }
    ;

elseif_list:
      ELSEIF LPAREN condition RPAREN stmt_block
        {
          $$ = createElseIf($3, $5);
        }
    | elseif_list ELSEIF LPAREN condition RPAREN stmt_block
        {
          $$ = createElseIfList($1, $4, $6);
        }
    ;

stmt_list:
      stmt  { $$ = $1; }
    | stmt_list stmt { $$ = createStmtList($1, $2); }
    ;

stmt_block:
      LBRACE stmt_list RBRACE  { $$ = $2; }
    | stmt                     { $$ = $1; }
    ;

condition:
      expression EQEQ expression { $$ = createCondition("==", $1, $3); }
    | expression NEQ expression  { $$ = createCondition("!=", $1, $3); }
    | expression LT expression   { $$ = createCondition("<", $1, $3); }
    | expression LE expression   { $$ = createCondition("<=", $1, $3); }
    | expression GT expression   { $$ = createCondition(">", $1, $3); }
    | expression GE expression   { $$ = createCondition(">=", $1, $3); }
    | condition AND condition    { $$ = createCondition("&&", $1, $3); }
    | condition OR condition     { $$ = createCondition("||", $1, $3); }
    | condition XOR condition    { $$ = createCondition("xor", $1, $3); }
    | NOT condition              { $$ = createCondition("!", $2, NULL); }
    | LPAREN condition RPAREN    { $$ = $2; }
    ;

for_stmt:
      FOR LPAREN loop_init SEMICOLON condition SEMICOLON loop_update RPAREN stmt_block
        {
          $$ = createFor($3, $5, $7, $9);
          printf("For loop created\n");
        }
    ;

loop_init:
      IDENTIFIER EQ expression { 
          if (!isVarDeclared($1)) {
              fprintf(stderr, "Error: variable '%s' not declared\n", $1);
              exit(1);
          }
          $$ = createAssign($1, $3);
      }
    | TYPE IDENTIFIER EQ expression {
          $$ = createAssign($2, $4);
          char varType;
          if (strcmp($1, "char") == 0) varType = 'c';
          else if (strcmp($1, "string") == 0) varType = 's';
          else varType = 'i';
          addVar($2, 1, $4->value, varType);
          printf("Loop variable declaration: %s\n", $2);
      }
    | /* empty */ { $$ = NULL; }
    ;

loop_update:
      IDENTIFIER EQ expression 
        {
          if (!isVarDeclared($1)) {
              fprintf(stderr, "Error: variable '%s' not declared\n", $1);
              exit(1);
          }
          $$ = createAssign($1, $3);
        }
    | /* empty */ { $$ = NULL; }
    ;

while_stmt:
      WHILE LPAREN condition RPAREN stmt_block
        {
          $$ = createWhile($3, $5);
          printf("While loop created\n");
        }
    ;

do_while_stmt:
      DO stmt_block WHILE LPAREN condition RPAREN SEMICOLON
        {
          $$ = createDoWhile($5, $2);
          printf("Do-while loop created\n");
        }
    ;

expression:
      NUMBER             { $$ = createNum($1); }
    | CHAR_LITERAL       { $$ = createChar($1); }
    | IDENTIFIER         { 
          if (!isVarDeclared($1)) {
              fprintf(stderr, "Error: variable '%s' not declared\n", $1);
              exit(1);
          }
          $$ = createVar($1); 
      }
    | array_access       { $$ = $1; }
    | '(' expression ')' { $$ = $2; }
    | expression PLUS expression     { $$ = createBinOp('+', $1, $3); }
    | expression MINUS expression    { $$ = createBinOp('-', $1, $3); }
    | expression MULTIPLY expression { $$ = createBinOp('*', $1, $3); }
    | expression DIVIDE expression   { $$ = createBinOp('/', $1, $3); }
    ;

%%

void yyerror(const char* s) {
    extern int yylineno;
    fprintf(stderr, "Syntax error at line %d: %s\n", yylineno, s);
}

int* extractInitValues(ASTNode* initList, int* count) {
    if (!initList) {
        *count = 0;
        return NULL;
    }
    
    *count = 0;
    ASTNode* cur = initList;
    while (cur) {
        (*count)++;
        cur = cur->next;
    }
    
    int* values = malloc((*count) * sizeof(int));
    cur = initList;
    int i = 0;
    while (cur && i < *count) {
        if (strcmp(cur->type, "num") == 0 || strcmp(cur->type, "char") == 0) {
            values[i] = cur->value;
        } else {
            values[i] = 0;
        }
        cur = cur->next;
        i++;
    }
    
    return values;
}
