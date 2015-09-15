%{
#include <stdio.h>

#define YY_DECL int yylex()
#define YY_DECL extern "C" int yylex()

%}

%%
[ \t]	; // ignore all whitespace
"class Program" 		{}
\n 						{return T_NEWLINE;}
"{"                     return TOKEN(TLBRACE);
"}"                     return TOKEN(TRBRACE);
"+"                     return TOKEN(TPLUS);
"-"                     return TOKEN(TMINUS);
"*"                     return TOKEN(TMUL);
"/"                     return TOKEN(TDIV);
%%
