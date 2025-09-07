%option noyywrap

%{
#include <stdio.h>
#include <string.h>

#define YY_DECL int yylex()

int words = 0;
int chars = 0;
int lines = 0;

/* Later, these would be used with a parser (Bison/Yacc): */
enum Tokens {
    TYPE = 256,
    KEYWORD,
    IDENTIFIER,
    NUMBER,
    SEMICOLON,
    EQ,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE
};
%}

letter      [a-zA-Z]
digit       [0-9]
ID          {letter}({letter}|{digit})*
delim       [ \t\n]
NUMBER      {digit}+(\.{digit}+)?(E[+\-]?{digit}+)?
ws          {delim}+

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

"int"   {words++; chars += strlen(yytext);
         printf("%s : TYPE\n", yytext);
         // return TYPE;
        }

"char"  {words++; chars += strlen(yytext);
         printf("%s : TYPE\n", yytext);
         // return TYPE;
        }

"write" {words++; chars += strlen(yytext);
         printf("%s : KEYWORD\n", yytext);
         // return KEYWORD;
        }

{ID}    {words++; chars += strlen(yytext);
         printf("%s : IDENTIFIER\n", yytext);
         // return IDENTIFIER;
        }

{NUMBER} {words++; chars += strlen(yytext);
          printf("%s : NUMBER\n", yytext);
          // return NUMBER;
         }

";"     {chars++;
         printf("%s : SEMICOLON\n", yytext);
         // return SEMICOLON;
        }

"="     {chars++;
         printf("%s : EQ\n", yytext);
         // return EQ;
        }

"+"     {chars++; printf("%s : PLUS\n", yytext); 
         // return PLUS;
        }

"-"     {chars++; printf("%s : MINUS\n", yytext); 
         // return MINUS;
        }

"*"     {chars++; printf("%s : MULTIPLY\n", yytext); 
         // return MULTIPLY;
        }

"/"     {chars++; printf("%s : DIVIDE\n", yytext); 
         // return DIVIDE;
        }

\r?\n   {lines++; chars=0;}
[ \t]   {chars++;}
.       {chars++;
         printf("%s : Unrecognized symbol at line %d char %d\n", yytext, lines, chars);
        }

%%

int main(int argc, char**argv)
{
    #ifdef YYDEBUG
        yydebug = 1;
    #endif

    printf("Compiler started. \n\n");

    if (argc > 1){
        if(!(yyin = fopen(argv[1], "r"))) {
            perror(argv[1]);
            return(1);
        }
    }
    yylex();
}
