%{
#include <stdio.h>

#define YY_DECL int yylex()
#include "parser.tab.h"
int line_num = 1;
%}

LETTER            [a-zA-Z_]
DIGIT             [0-9]
LETTERDIGIT       [a-zA-Z0-9_]

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
[DIGIT]+				{printf("%s\n", "INT_DECLARATION");yylval.ival = atoi(yytext); return T_INT; }
\"(\\.|[^"])\"		   	{return CHAR_LITERAL;}
\"(\\.|[^"])*\"		    {return STRING_LITERAL;}
{LETTER}{LETTERDIGIT}*  {printf("ID: %s\n", yytext); return IDENTIFIER; }

%%