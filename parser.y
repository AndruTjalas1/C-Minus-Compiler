%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AST.h"   /* AST node definitions */

/* Lexer functions */
extern int yylex();
extern FILE* yyin;

/* Root of the AST */
ASTNode* root = NULL;

void yyerror(const char* s);

%}

/* Semantic values union */
%union {
    int num;               /* For numeric literals */
    char* str;             /* For identifiers */
    ASTNode* node;         /* For AST nodes */
}

/* Tokens with semantic types */
%token <str> IDENTIFIER
%token <num> NUMBER
%token TYPE SEMICOLON EQ PLUS MINUS MULTIPLY DIVIDE
%token LBRACKET RBRACKET COMMA KEYWORD

/* Non-terminals with semantic types */
%type <node> program declaration expression

/* Operator precedence */
%left PLUS MINUS
%left MULTIPLY DIVIDE

%%

program:
      program declaration { root = createStmtList(root, $2); $$ = root; }
    | /* empty */          { $$ = NULL; }
    ;

declaration:
      TYPE IDENTIFIER SEMICOLON
        { 
          $$ = createDecl($2); 
          printf("Variable declaration: %s\n", $2); 
        }
    | TYPE IDENTIFIER EQ expression SEMICOLON
        { 
          $$ = createAssign($2, $4);
          printf("Initialized variable: %s\n", $2);
        }
    | TYPE IDENTIFIER LBRACKET NUMBER RBRACKET SEMICOLON
        { 
          $$ = createArrayDecl($2, $4);
          printf("Array declaration: %s[%d]\n", $2, $4);
        }
    | TYPE IDENTIFIER LBRACKET NUMBER RBRACKET LBRACKET NUMBER RBRACKET SEMICOLON
        { 
          $$ = create2DArrayDecl($2, $4, $7);
          printf("2D Array declaration: %s[%d][%d]\n", $2, $4, $7);
        }
    ;

expression:
      NUMBER             { $$ = createNum($1); }
    | IDENTIFIER         { $$ = createVar($1); }
    | '(' expression ')' { $$ = $2; }
    | expression PLUS expression     { $$ = createBinOp('+', $1, $3); }
    | expression MINUS expression    { $$ = createBinOp('-', $1, $3); }
    | expression MULTIPLY expression { $$ = createBinOp('*', $1, $3); }
    | expression DIVIDE expression   { $$ = createBinOp('/', $1, $3); }
    ;

%%

int main(int argc, char** argv) {
    printf("Parser started.\n");

    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            perror(argv[1]);
            return 1;
        }
    }

    yyparse();

    /* Print AST for debugging */
    printAST(root, 0);

    return 0;
}

/* Error handling */
void yyerror(const char* s) {
    extern int yylineno;  // Provided by Flex
    fprintf(stderr, "Syntax error at line %d: %s\n", yylineno, s);
}
