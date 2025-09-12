%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yylex(void);
int yyerror(char *s);

/* You can put globals here if needed */
extern FILE *yyin;
%}

%union {
    char *str;
    int num;
}

/* Tokens */
%token <str> IDENTIFIER
%token <num> NUMBER
%token TYPE SEMICOLON EQ PLUS MINUS MULTIPLY DIVIDE
%token LBRACKET RBRACKET COMMA KEYWORD

/* Operator precedence */
%left PLUS MINUS
%left MULTIPLY DIVIDE

%%  /* Grammar rules start here */

program:
    program declaration
    | /* empty */
    ;

declaration:
      TYPE IDENTIFIER SEMICOLON
        { printf("Variable declaration: %s\n", $2); }
    | TYPE IDENTIFIER EQ expression SEMICOLON
        { printf("Initialized variable: %s\n", $2); }
    | TYPE IDENTIFIER LBRACKET NUMBER RBRACKET SEMICOLON
        { printf("Array declaration: %s[%d]\n", $2, $4); }
    | TYPE IDENTIFIER LBRACKET NUMBER RBRACKET LBRACKET NUMBER RBRACKET SEMICOLON
        { printf("2D Array declaration: %s[%d][%d]\n", $2, $4, $7); }
    ;

expression:
      NUMBER
    | IDENTIFIER
    | '(' expression ')'
    | expression PLUS expression
    | expression MINUS expression
    | expression MULTIPLY expression
    | expression DIVIDE expression
;

%%  /* Grammar ends here. User C code goes below */

int main(int argc, char **argv) {
    printf("Parser started.\n");

    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            perror(argv[1]);
            return 1;
        }
    }

    yyparse();
    return 0;
}

int yyerror(char *s) {
    fprintf(stderr, "Error: %s\n", s);
    return 0;
}
