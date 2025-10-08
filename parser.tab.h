/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IDENTIFIER = 258,              /* IDENTIFIER  */
    TYPE = 259,                    /* TYPE  */
    NUMBER = 260,                  /* NUMBER  */
    CHAR_LITERAL = 261,            /* CHAR_LITERAL  */
    STRING_LITERAL = 262,          /* STRING_LITERAL  */
    SEMICOLON = 263,               /* SEMICOLON  */
    EQ = 264,                      /* EQ  */
    PLUS = 265,                    /* PLUS  */
    MINUS = 266,                   /* MINUS  */
    MULTIPLY = 267,                /* MULTIPLY  */
    DIVIDE = 268,                  /* DIVIDE  */
    MODULO = 269,                  /* MODULO  */
    PLUSEQ = 270,                  /* PLUSEQ  */
    MINUSEQ = 271,                 /* MINUSEQ  */
    MULTEQ = 272,                  /* MULTEQ  */
    DIVEQ = 273,                   /* DIVEQ  */
    MODEQ = 274,                   /* MODEQ  */
    PLUSPLUS = 275,                /* PLUSPLUS  */
    MINUSMINUS = 276,              /* MINUSMINUS  */
    LBRACKET = 277,                /* LBRACKET  */
    RBRACKET = 278,                /* RBRACKET  */
    LBRACE = 279,                  /* LBRACE  */
    RBRACE = 280,                  /* RBRACE  */
    COMMA = 281,                   /* COMMA  */
    KEYWORD = 282,                 /* KEYWORD  */
    LPAREN = 283,                  /* LPAREN  */
    RPAREN = 284,                  /* RPAREN  */
    IF = 285,                      /* IF  */
    ELSEIF = 286,                  /* ELSEIF  */
    ELSE = 287,                    /* ELSE  */
    FOR = 288,                     /* FOR  */
    WHILE = 289,                   /* WHILE  */
    DO = 290,                      /* DO  */
    FUNCTION = 291,                /* FUNCTION  */
    RETURN = 292,                  /* RETURN  */
    EQEQ = 293,                    /* EQEQ  */
    NEQ = 294,                     /* NEQ  */
    LT = 295,                      /* LT  */
    LE = 296,                      /* LE  */
    GT = 297,                      /* GT  */
    GE = 298,                      /* GE  */
    AND = 299,                     /* AND  */
    OR = 300,                      /* OR  */
    NOT = 301,                     /* NOT  */
    XOR = 302,                     /* XOR  */
    TRUE = 303,                    /* TRUE  */
    FALSE = 304                    /* FALSE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 20 "parser.y"

    int num;
    char* str;
    char character;
    ASTNode* node;

#line 120 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
