%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "symtab.h"
#include "error.h"

extern int yylex();
extern FILE* yyin;
extern int yylineno;
extern char* yytext;

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
%token SEMICOLON EQ PLUS MINUS MULTIPLY DIVIDE MODULO
%token PLUSEQ MINUSEQ MULTEQ DIVEQ MODEQ
%token PLUSPLUS MINUSMINUS
%token LBRACKET RBRACKET LBRACE RBRACE COMMA KEYWORD COLON
%token LPAREN RPAREN
%token IF ELSEIF ELSE
%token FOR WHILE DO
%token SWITCH CASE DEFAULT BREAK CONTINUE
%token FUNCTION RETURN
%token EQEQ NEQ LT LE GT GE
%token AND OR NOT XOR
%token <num> TRUE FALSE

%expect 5

%type <node> program stmt declaration assignment expression print_stmt
%type <node> array_access init_list if_stmt condition stmt_block elseif_list stmt_list
%type <node> for_stmt while_stmt do_while_stmt loop_init loop_update
%type <node> switch_stmt case_list case_stmt
%type <node> function_def param_list param function_call arg_list return_stmt

%left OR
%left XOR
%left AND
%right NOT
%left EQEQ NEQ
%left LT LE GT GE
%left PLUS MINUS
%left MULTIPLY DIVIDE MODULO

%%

program:
      program stmt          { root = createStmtList(root, $2); $$ = root; }
    | program function_def  { root = createStmtList(root, $2); $$ = root; }
    | /* empty */           { $$ = NULL; }
    ;

stmt:
      declaration
    | assignment
    | print_stmt
    | if_stmt
    | for_stmt
    | while_stmt
    | do_while_stmt
    | switch_stmt
    | BREAK SEMICOLON { $$ = createBreak(); }
    | CONTINUE SEMICOLON { $$ = createContinue(); }
    | function_call SEMICOLON { $$ = $1; }
    | return_stmt
    ;

declaration:
      TYPE IDENTIFIER SEMICOLON
        { 
          $$ = createDecl($2);
          char varType;
          if (strcmp($1, "char") == 0) varType = 'c';
          else if (strcmp($1, "string") == 0) varType = 's';
          else if (strcmp($1, "bool") == 0) varType = 'b';
          else varType = 'i';
          addVar($2, 1, 0, varType);
          // printf("Variable declaration: %s\n", $2); 
        }
    | TYPE IDENTIFIER EQ expression SEMICOLON
        { 
          $$ = createAssign($2, $4);
          char varType;
          if (strcmp($1, "char") == 0) varType = 'c';
          else if (strcmp($1, "string") == 0) varType = 's';
          else if (strcmp($1, "bool") == 0) varType = 'b';
          else varType = 'i';
          addVar($2, 1, $4->value, varType);
          // printf("Initialized variable: %s\n", $2);
        }
    | TYPE IDENTIFIER LBRACKET NUMBER RBRACKET EQ LBRACE init_list RBRACE SEMICOLON
        { 
          int initCount;
          int* initValues = extractInitValues($8, &initCount);
          $$ = createArrayDeclInit($2, $4, $8);
          char varType = (strcmp($1, "char") == 0) ? 'c' : 'i';
          addArrayWithInit($2, $4, varType, initValues, initCount);
          // printf("Initialized array declaration: %s[%d] with %d values\n", $2, $4, initCount);
        }
    | TYPE IDENTIFIER LBRACKET NUMBER RBRACKET SEMICOLON
        { 
          $$ = createArrayDecl($2, $4);
          char varType = (strcmp($1, "char") == 0) ? 'c' : 'i';
          addArray($2, $4, varType);
          // printf("Array declaration: %s[%d]\n", $2, $4);
        }
    | TYPE IDENTIFIER LBRACKET NUMBER RBRACKET LBRACKET NUMBER RBRACKET SEMICOLON
        { 
          $$ = create2DArrayDecl($2, $4, $7);
          char varType = (strcmp($1, "char") == 0) ? 'c' : 'i';
          add2DArray($2, $4, $7, varType);
          // printf("2D Array declaration: %s[%d][%d]\n", $2, $4, $7);
        }
    | TYPE IDENTIFIER LBRACKET NUMBER RBRACKET LBRACKET NUMBER RBRACKET EQ LBRACE init_list RBRACE SEMICOLON
        { 
          int initCount;
          int* initValues = extractInitValues($11, &initCount);
          $$ = create2DArrayDeclInit($2, $4, $7, $11);
          char varType = (strcmp($1, "char") == 0) ? 'c' : 'i';
          add2DArrayWithInit($2, $4, $7, varType, initValues, initCount);
          // printf("Initialized 2D array declaration: %s[%d][%d] with %d values\n", $2, $4, $7, initCount);
        }
    | TYPE IDENTIFIER EQ STRING_LITERAL SEMICOLON
        {
            if (strcmp($1, "string") == 0) {
                $$ = createStringDecl($2, $4);
                addStringVar($2, $4);
                // printf("String declaration: %s = \"%s\"\n", $2, $4);
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
              errorUndeclaredVariable(yylineno, $1);
              exit(1);
          }
          $$ = createAssign($1, $3); 
          // printf("Assignment: %s\n", $1);
        }
    | IDENTIFIER PLUSEQ expression SEMICOLON
        {
          if (!isVarDeclared($1)) {
              errorUndeclaredVariable(yylineno, $1);
              exit(1);
          }
          ASTNode* var = createVar($1);
          ASTNode* add = createBinOp('+', var, $3);
          $$ = createAssign($1, add);
          // printf("Compound assignment: %s += \n", $1);
        }
    | IDENTIFIER MINUSEQ expression SEMICOLON
        {
          if (!isVarDeclared($1)) {
              errorUndeclaredVariable(yylineno, $1);
              exit(1);
          }
          ASTNode* var = createVar($1);
          ASTNode* sub = createBinOp('-', var, $3);
          $$ = createAssign($1, sub);
          // printf("Compound assignment: %s -= \n", $1);
        }
    | IDENTIFIER MULTEQ expression SEMICOLON
        {
          if (!isVarDeclared($1)) {
              errorUndeclaredVariable(yylineno, $1);
              exit(1);
          }
          ASTNode* var = createVar($1);
          ASTNode* mul = createBinOp('*', var, $3);
          $$ = createAssign($1, mul);
          // printf("Compound assignment: %s *= \n", $1);
        }
    | IDENTIFIER DIVEQ expression SEMICOLON
        {
          if (!isVarDeclared($1)) {
              errorUndeclaredVariable(yylineno, $1);
              exit(1);
          }
          ASTNode* var = createVar($1);
          ASTNode* div = createBinOp('/', var, $3);
          $$ = createAssign($1, div);
          // printf("Compound assignment: %s /= \n", $1);
        }
    | IDENTIFIER MODEQ expression SEMICOLON
        {
          if (!isVarDeclared($1)) {
              errorUndeclaredVariable(yylineno, $1);
              exit(1);
          }
          ASTNode* var = createVar($1);
          ASTNode* mod = createBinOp('%', var, $3);
          $$ = createAssign($1, mod);
          // printf("Compound assignment: %s %%= \n", $1);
        }
    | IDENTIFIER PLUSPLUS SEMICOLON
        {
          if (!isVarDeclared($1)) {
              errorUndeclaredVariable(yylineno, $1);
              exit(1);
          }
          ASTNode* var = createVar($1);
          ASTNode* one = createNum(1);
          ASTNode* add = createBinOp('+', var, one);
          $$ = createAssign($1, add);
          // printf("Post-increment: %s++\n", $1);
        }
    | IDENTIFIER MINUSMINUS SEMICOLON
        {
          if (!isVarDeclared($1)) {
              errorUndeclaredVariable(yylineno, $1);
              exit(1);
          }
          ASTNode* var = createVar($1);
          ASTNode* one = createNum(1);
          ASTNode* sub = createBinOp('-', var, one);
          $$ = createAssign($1, sub);
          // printf("Post-decrement: %s--\n", $1);
        }
    | PLUSPLUS IDENTIFIER SEMICOLON
        {
          if (!isVarDeclared($2)) {
              errorUndeclaredVariable(yylineno, $2);
              exit(1);
          }
          ASTNode* var = createVar($2);
          ASTNode* one = createNum(1);
          ASTNode* add = createBinOp('+', var, one);
          $$ = createAssign($2, add);
          // printf("Pre-increment: ++%s\n", $2);
        }
    | MINUSMINUS IDENTIFIER SEMICOLON
        {
          if (!isVarDeclared($2)) {
              errorUndeclaredVariable(yylineno, $2);
              exit(1);
          }
          ASTNode* var = createVar($2);
          ASTNode* one = createNum(1);
          ASTNode* sub = createBinOp('-', var, one);
          $$ = createAssign($2, sub);
          // printf("Pre-decrement: --%s\n", $2);
        }
    | array_access EQ expression SEMICOLON
        {
          $$ = createArrayAssign($1, $3);
          // printf("Array assignment\n");
        }
    ;

print_stmt:
      KEYWORD LPAREN expression RPAREN SEMICOLON
        {
           $$ = createPrint($3);
            // printf("Print statement created\n");
        }
    ;

array_access:
      IDENTIFIER LBRACKET expression RBRACKET
        {
          if (!isVarDeclared($1)) {
              errorUndeclaredVariable(yylineno, $1);
              exit(1);
          }
          $$ = createArrayAccess($1, $3);
        }
    | IDENTIFIER LBRACKET expression RBRACKET LBRACKET expression RBRACKET
        {
          if (!isVarDeclared($1)) {
              errorUndeclaredVariable(yylineno, $1);
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
          // printf("If statement created\n");
        }
    | IF LPAREN condition RPAREN stmt_block ELSE stmt_block
        {
          $$ = createIf($3, $5, NULL, $7);
          // printf("If-else statement created\n");
        }
    | IF LPAREN condition RPAREN stmt_block elseif_list
        {
          $$ = createIf($3, $5, $6, NULL);
          // printf("If-elseif statement created\n");
        }
    | IF LPAREN condition RPAREN stmt_block elseif_list ELSE stmt_block
        {
          $$ = createIf($3, $5, $6, $8);
          // printf("If-elseif-else statement created\n");
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
          // printf("For loop created\n");
        }
    ;

loop_init:
      IDENTIFIER EQ expression { 
          if (!isVarDeclared($1)) {
              errorUndeclaredVariable(yylineno, $1);
              exit(1);
          }
          $$ = createAssign($1, $3);
      }
    | TYPE IDENTIFIER EQ expression {
          $$ = createAssign($2, $4);
          char varType;
          if (strcmp($1, "char") == 0) varType = 'c';
          else if (strcmp($1, "string") == 0) varType = 's';
          else if (strcmp($1, "bool") == 0) varType = 'b';
          else varType = 'i';
          addVar($2, 1, $4->value, varType);
          // printf("Loop variable declaration: %s\n", $2);
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
    | IDENTIFIER PLUSPLUS
        {
          if (!isVarDeclared($1)) {
              fprintf(stderr, "Error: variable '%s' not declared\n", $1);
              exit(1);
          }
          ASTNode* var = createVar($1);
          ASTNode* one = createNum(1);
          ASTNode* add = createBinOp('+', var, one);
          $$ = createAssign($1, add);
        }
    | IDENTIFIER MINUSMINUS
        {
          if (!isVarDeclared($1)) {
              fprintf(stderr, "Error: variable '%s' not declared\n", $1);
              exit(1);
          }
          ASTNode* var = createVar($1);
          ASTNode* one = createNum(1);
          ASTNode* sub = createBinOp('-', var, one);
          $$ = createAssign($1, sub);
        }
    | PLUSPLUS IDENTIFIER
        {
          if (!isVarDeclared($2)) {
              fprintf(stderr, "Error: variable '%s' not declared\n", $2);
              exit(1);
          }
          ASTNode* var = createVar($2);
          ASTNode* one = createNum(1);
          ASTNode* add = createBinOp('+', var, one);
          $$ = createAssign($2, add);
        }
    | MINUSMINUS IDENTIFIER
        {
          if (!isVarDeclared($2)) {
              fprintf(stderr, "Error: variable '%s' not declared\n", $2);
              exit(1);
          }
          ASTNode* var = createVar($2);
          ASTNode* one = createNum(1);
          ASTNode* sub = createBinOp('-', var, one);
          $$ = createAssign($2, sub);
        }
    | /* empty */ { $$ = NULL; }
    ;

while_stmt:
      WHILE LPAREN condition RPAREN stmt_block
        {
          $$ = createWhile($3, $5);
          // printf("While loop created\n");
        }
    ;

do_while_stmt:
      DO stmt_block WHILE LPAREN condition RPAREN SEMICOLON
        {
          $$ = createDoWhile($5, $2);
          // printf("Do-while loop created\n");
        }
    ;

switch_stmt:
      SWITCH LPAREN expression RPAREN LBRACE case_list RBRACE
        {
          $$ = createSwitch($3, $6);
          // printf("Switch statement created\n");
        }
    ;

case_list:
      case_stmt { $$ = $1; }
    | case_list case_stmt { $$ = createCaseList($1, $2); }
    ;

case_stmt:
      CASE expression COLON stmt_list
        {
          $$ = createCase($2, $4);
        }
    | DEFAULT COLON stmt_list
        {
          $$ = createDefaultCase($3);
        }
    ;

function_def:
      FUNCTION TYPE IDENTIFIER LPAREN param_list RPAREN 
        {
          // Mid-rule action: Add function and parameters BEFORE parsing body
          if (!addFunction($3, $2, $5)) {
              fprintf(stderr, "Failed to add function '%s'\n", $3);
              exit(1);
          }
          
          // Enter function scope - this will add parameters to symbol table
          enterFunctionScope($3);
        }
      LBRACE stmt_list RBRACE
        {
          $$ = createFunctionDecl($2, $3, $5, $9);
          exitFunctionScope();
          // printf("Function declaration: %s\n", $3);
        }
    | FUNCTION TYPE IDENTIFIER LPAREN RPAREN 
        {
          // Mid-rule action for function with no parameters
          if (!addFunction($3, $2, NULL)) {
              fprintf(stderr, "Failed to add function '%s'\n", $3);
              exit(1);
          }
          
          // Enter function scope
          enterFunctionScope($3);
        }
      LBRACE stmt_list RBRACE
        {
          $$ = createFunctionDecl($2, $3, NULL, $8);
          exitFunctionScope();
          // printf("Function declaration: %s (no params)\n", $3);
        }
    ;

param_list:
      param                      { $$ = $1; }
    | param_list COMMA param     { $$ = createParamList($1, $3); }
    ;

param:
      TYPE IDENTIFIER
        {
          $$ = createParam($1, $2);
        }
    ;

function_call:
      IDENTIFIER LPAREN arg_list RPAREN
        {
          if (!validateFunctionCall($1, $3)) {
              exit(1);
          }
          $$ = createFunctionCall($1, $3);
        }
    | IDENTIFIER LPAREN RPAREN
        {
          if (!validateFunctionCall($1, NULL)) {
              exit(1);
          }
          $$ = createFunctionCall($1, NULL);
        }
    ;

arg_list:
      expression                 { $$ = $1; }
    | arg_list COMMA expression  { $$ = createArgList($1, $3); }
    ;

return_stmt:
      RETURN expression SEMICOLON
        {
          $$ = createReturn($2);
        }
    | RETURN SEMICOLON
        {
          $$ = createReturn(NULL);
        }
    ;

expression:
      NUMBER             { $$ = createNum($1); }
    | CHAR_LITERAL       { $$ = createChar($1); }
    | STRING_LITERAL     { $$ = createStringLiteral($1); }
    | TRUE               { $$ = createBool(1); }
    | FALSE              { $$ = createBool(0); }
    | IDENTIFIER         { 
          if (!isVarDeclared($1) && !isFunctionDeclared($1)) {
              errorUndeclaredVariable(yylineno, $1);
              exit(1);
          }
          $$ = createVar($1); 
      }
    | function_call      { $$ = $1; }
    | array_access       { $$ = $1; }
    | '(' expression ')' { $$ = $2; }
    | expression PLUS expression     { $$ = createBinOp('+', $1, $3); }
    | expression MINUS expression    { $$ = createBinOp('-', $1, $3); }
    | expression MULTIPLY expression { $$ = createBinOp('*', $1, $3); }
    | expression DIVIDE expression   { $$ = createBinOp('/', $1, $3); }
    | expression MODULO expression   { $$ = createBinOp('%', $1, $3); }
    ;

%%

void yyerror(const char* s) {
    // Try to provide more context about the error
    if (strstr(s, "syntax error")) {
        if (yytext && strlen(yytext) > 0) {
            reportError(yylineno, yytext, ERROR_SYNTAX, 
                       "Unexpected token or syntax error");
        } else {
            reportError(yylineno, "", ERROR_SYNTAX, 
                       "Syntax error in source code");
        }
    } else {
        reportError(yylineno, yytext ? yytext : "", ERROR_SYNTAX, s);
    }
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
