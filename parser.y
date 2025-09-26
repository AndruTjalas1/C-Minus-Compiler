%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AST.h"
#include "symtab.h"

extern int yylex();
extern FILE* yyin;

ASTNode* root = NULL;

void yyerror(const char* s);
%}

/* Semantic values union */
%union {
    int num;               /* For numeric literals */
    char* str;             /* For identifiers and type names */
    char character;        /* For character literals */
    ASTNode* node;         /* For AST nodes */
}

/* Tokens */
%token <str> IDENTIFIER
%token <str> TYPE
%token <num> NUMBER
%token <character> CHAR_LITERAL
%token SEMICOLON EQ PLUS MINUS MULTIPLY DIVIDE
%token LBRACKET RBRACKET COMMA KEYWORD
%token LPAREN RPAREN

/* Non-terminals with types */
%type <node> program stmt declaration assignment expression print_stmt
%type <node> array_access

/* Operator precedence */
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
    ;

declaration:
      TYPE IDENTIFIER SEMICOLON
        { 
          $$ = createDecl($2); 
          char varType = (strcmp($1, "char") == 0) ? 'c' : 'i';
          addVar($2, 1, 0, varType);
          printf("Variable declaration: %s\n", $2); 
        }
    | TYPE IDENTIFIER EQ expression SEMICOLON
        { 
          $$ = createAssign($2, $4);
          char varType = (strcmp($1, "char") == 0) ? 'c' : 'i';
          addVar($2, 1, $4->value, varType);
          printf("Initialized variable: %s\n", $2);
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

/* Error handling */
void yyerror(const char* s) {
    extern int yylineno;  // Provided by Flex
    fprintf(stderr, "Syntax error at line %d: %s\n", yylineno, s);
}