%option noyywrap
%option yylineno

%{
#include <stdio.h>
#include <string.h>
#include "AST.h"
#include "parser.tab.h"

#define YY_DECL int yylex()
%}

letter [a-zA-Z]
digit [0-9]
ID {letter}({letter}|{digit})*
NUMBER {digit}+(\.{digit}+)?(E[+\-]?{digit}+)?
CHAR_LITERAL '.'
STRING \"[^\"]*\"

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

"int"       { 
    yylval.str = strdup("int"); 
    return TYPE; 
}
"char"      { 
    yylval.str = strdup("char"); 
    return TYPE; 
}
"string"    { 
    yylval.str = strdup("string"); 
    return TYPE; 
}
"bool"      { 
    yylval.str = strdup("bool"); 
    return TYPE; 
}

"write"     { return KEYWORD; }
"true"      { 
    yylval.num = 1; 
    return TRUE; 
}
"false"     { 
    yylval.num = 0; 
    return FALSE; 
}
"if"        { return IF; }
"elseif"    { return ELSEIF; }
"else"      { return ELSE; }
"for"       { return FOR; }
"while"     { return WHILE; }
"do"        { return DO; }

{ID}        { 
    yylval.str = strdup(yytext); 
    return IDENTIFIER; 
}

{NUMBER}    { 
    yylval.num = atoi(yytext); 
    return NUMBER; 
}

{CHAR_LITERAL} { 
    yylval.character = yytext[1]; 
    return CHAR_LITERAL; 
}

{STRING}    {
    yylval.str = strndup(yytext + 1, strlen(yytext) - 2);
    return STRING_LITERAL;
}

"+="        { return PLUSEQ; }
"-="        { return MINUSEQ; }
"*="        { return MULTEQ; }
"/="        { return DIVEQ; }
"%="        { return MODEQ; }
"++"        { return PLUSPLUS; }
"--"        { return MINUSMINUS; }
"%"         { return MODULO; }
";"         { return SEMICOLON; }
"["         { return LBRACKET; }
"]"         { return RBRACKET; }
"{"         { return LBRACE; }
"}"         { return RBRACE; }
","         { return COMMA; }
"&&"        { return AND; }
"||"        { return OR; }
"!"         { return NOT; }
"^"         { return XOR; }
"=="        { return EQEQ; }
"="         { return EQ; }
"!="        { return NEQ; }
"<"         { return LT; }
"<="        { return LE; }
">"         { return GT; }
">="        { return GE; }
"+"         { return PLUS; }
"-"         { return MINUS; }
"*"         { return MULTIPLY; }
"/"         { return DIVIDE; }
"("         { return LPAREN; }
")"         { return RPAREN; }

\r?\n       { }
[ \t]       { }

.           { 
    printf("Unrecognized symbol '%s' at line %d\n", yytext, yylineno); 
    return 0; 
}

%%