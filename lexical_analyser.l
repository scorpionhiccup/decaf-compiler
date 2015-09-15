%{
#include <stdio.h>

#define YY_DECL int yylex()
#include "parser.tab.h"
%}

%%
[ \t]	; // ignore all whitespace
"class Program" 		{return START;}
\n 						{return T_NEWLINE;}
"{"                     {return LBRACE;}
"}"                     {return RBRACE;}
"["                     {return TLSQUARE;}
"]"                     {return TRSQUARE;}
"callout"               {return CALLOUT;}
"boolean"				{return BOOLEAN;}
"false"					{return FALSE;}
"true"					{return TRUE;}
"+"                     {return TPLUS;}
"-"                     {return TMINUS;}
"*"                     {return TMUL;}
"/"                     {return TDIV;}
[0-9]+					{yylval.ival = atoi(yytext); return T_INT; }
\"(\\.|[^"])*\"		    {return STRING_LITERAL;}
[a-zA-Z][A-Za-z_0-9]+   { return IDENTIFIER; }
%%
