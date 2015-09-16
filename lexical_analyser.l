%{
#include <stdio.h>

#define YY_DECL int yylex()
#include "parser.tab.h"
int line_num = 1;
%}

LETTER            [a-zA-Z_]
DIGIT             [0-9]
ALPHANUMERICAL       [a-zA-Z0-9_]

%%
[\n]	{++line_num;} 
[ \t]	; // ignore all whitespace
"class Program" 		{printf("%s\n", "CLASS");return START;}
";"						{return SEMI_COLON;}
"{"                     {return LBRACE;}
"}"                     {return RBRACE;}
"["                     {return TLSQUARE;}
"]"                     {return TRSQUARE;}
"("                     {return TLROUND;}
")"                     {return TRROUND;}
","						{return TCOMMA;}
"callout"               {printf("%s\n", "CALLOUT");return CALLOUT;}
"int"					{printf("%s\n", "INT_DECLARATION");return INT;}
"boolean"				{printf("%s\n", "BOOLEAN_DECLARATION");return BOOLEAN;}
"false"					{printf("%s\n", "BOOLEAN: false");return FALSE;}
"true"					{printf("%s\n", "BOOLEAN: true");return TRUE;}
"="                     {return TEQUAL;}
"+"                     {return TPLUS;}
"-"                     {return TMINUS;}
"*"                     {return TMUL;}
"/"                     {return TDIV;}
"!"						{return NOT;}
"%"						{return MOD;}
">"						{return TGREAT;}
"<"						{return TLESS;}
{DIGIT}+				{printf("INT: %s\n", yytext);yylval.number = atoi(yytext); return T_INT; }
\"(\\.|[^"])\"		   	{printf("CHARACTER: %s\n", yytext); return CHAR_LITERAL;}
\"(\\.|[^"])*\"		    {printf("STRING: %s\n", yytext); return STRING_LITERAL;}
{LETTER}{ALPHANUMERICAL}*  {printf("ID: %s\n", yytext); return IDENTIFIER; }

%%