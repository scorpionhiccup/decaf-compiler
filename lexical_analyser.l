%{
#include <stdio.h>

#define YY_DECL int yylex()
#include "parser.tab.h"
%}

%%
[ \t]	; // ignore all whitespace
"class Program" 		{return START;}
\n 						{return T_NEWLINE;}
"{"                     {return TLBRACE;}
"}"                     {return TRBRACE;}
"+"                     {return TPLUS;}
"-"                     {return TMINUS;}
"*"                     {return TMUL;}
"/"                     {return TDIV;}
%%
