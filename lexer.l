%option noyywrap
%option yylineno

%{
#include <stdio.h>
#include <string.h>
#include "AST.h"
#include "parser.tab.h"   // Bison token definitions
#define YY_DECL int yylex()
%}

letter      [a-zA-Z]
digit       [0-9]
ID          {letter}({letter}|{digit})*
NUMBER      {digit}+(\.{digit}+)?(E[+\-]?{digit}+)? 

%%

"/*" {
    int c;
    while((c = input()) != 0) {
        if(c == '*') {
            if((c = input()) == '/')
                break;
            else
                unput(c);
        }
    }
}

"int"       { return TYPE; }
"char"      { return TYPE; }
"write"     { return KEYWORD; }

{ID}        { yylval.str = strdup(yytext); return IDENTIFIER; }
{NUMBER}    { yylval.num = atoi(yytext); return NUMBER; }

";"         { return SEMICOLON; }
"["         { return LBRACKET; }
"]"         { return RBRACKET; }
","         { return COMMA; }
"="         { return EQ; }
"+"         { return PLUS; }
"-"         { return MINUS; }
"*"         { return MULTIPLY; }
"/"         { return DIVIDE; }
"("         { return LPAREN; }
")"         { return RPAREN; }

\r?\n       { /* Flex increments yylineno automatically */ }
[ \t]       { /* ignore spaces/tabs */ }

.           { 
    printf("Unrecognized symbol '%s' at line %d\n", yytext, yylineno);
    return 0; 
}

%%
