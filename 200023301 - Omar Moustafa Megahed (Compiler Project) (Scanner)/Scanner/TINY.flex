%{
#include "tokens.h"
#include "globals.h"
#include "util.h"
#include "scan.h"

/* lexeme of identifier or reserved word */
char tokenString[MAXTOKENLEN+1];
%}

DIGIT       [0-9]
LETTER      [a-zA-Z]
WHITESPACE  [ \t]
NEWLINE     \n

%%
"if"            {return IF;}
"else"          {return ELSE;}
"int"           {return INT;}
"void"          {return VOID;}
"return"        {return RETURN;}
"while"         {return WHILE;}
"do"            {return DO;}
"for"           {return FOR;}
"break"         {return BREAK;}
"continue"      {return CONTINUE;}

"="             {return ASSIGN;}
"=="            {return EQ;}
"<"             {return LT;}
">"             {return GT;}
"<="            {return LE;}
">="            {return GE;}
"!="            {return NE;}
"+"             {return PLUS;}
"-"             {return MINUS;}
"*"             {return TIMES;}
"/"             {return OVER;}
"("             {return LPAREN;}
")"             {return RPAREN;}
";"             {return SEMI;}
"["             {return LBRACKET;}
"]"             {return RBRACKET;}
","             {return COMMA;}
"&&"            {return AND;}
"||"            {return OR;}
"!"             {return NOT;}
"+="            {return PLUSEQ;}
"-="            {return MINUSEQ;}
"*="            {return TIMESEQ;}
"/="            {return DIVEQ;}
"++"            {return PLUSPLUS;}
"--"            {return MINUSMINUS;}

{LETTER}({LETTER}|{DIGIT})*  {return ID;}
{DIGIT}+        {return NUM;}
{WHITESPACE}+   {/* skip whitespace */}
{NEWLINE}       {lineno++;}
"//".*\n        {lineno++; /* skip single-line comments */}
"/*"([^*]|"*"[^/])*"*/" {
                    /* Count newlines in multi-line comments */
                    char* p = yytext;
                    while (*p) {
                        if (*p == '\n') lineno++;
                        p++;
                    }
                }
":"             {return ERROR; /* Single colon is not allowed */}
.               {return ERROR;}
%%

int yywrap(void) {
    return 1;
}