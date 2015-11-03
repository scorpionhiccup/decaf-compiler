%{

#include <iostream>
#include <string>
#define YY_DECL int yylex()
#include <list>

#include "AST.h"
#include "Visitor.h"
#include "parser.tab.h"
using namespace std;

%}

%option nodefault
%option noyywrap
%option yylineno

LETTER            		[a-zA-Z_]
DIGIT             		[0-9]
ALPHANUMERICAL       	[a-zA-Z0-9_]

%%
[\n]					{} 
[ \t]+	; // ignore all whitespace
"class" 				{fprintf(yyout,"%s\n", "CLASS");return START;}
";"						{return SEMI_COLON;}
"{"                     {return LBRACE;}
"}"                     {return RBRACE;}
"["                     {return TLSQUARE;}
"]"                     {return TRSQUARE;}
"("                     {return TLROUND;}
")"                     {return TRROUND;}
","						{return TCOMMA;}
"callout"               {fprintf(yyout, "%s\n", "CALLOUT");return CALLOUT;}
"int"					{fprintf(yyout,"%s\n", "INT_DECLARATION");return INT;}
"boolean"				{fprintf(yyout,"%s\n", "BOOLEAN_DECLARATION");return BOOLEAN;}
"false"					{fprintf(yyout,"%s\n", "BOOLEAN: false");yylval.bval=0;return FALSE;}
"true"					{fprintf(yyout,"%s\n", "BOOLEAN: true");yylval.bval=1;return TRUE;}
"<="					{return LE;}
">="					{return GE;}
"=="					{return EQ;}
"&&"					{return AND;}
"||"					{return OR;}
"!=" 					{return NOT_EQUAL;}
"="                     {return TEQUAL;}
"*"                     {return TMUL;}
"/"                     {return TDIV;}
"%"						{return MOD;}
"+"                     {return TPLUS;}
"-"                     {return TMINUS;}
"!"						{return NOT;}
">"						{return TGREAT;}
"<"						{return TLESS;}
{DIGIT}+				{fprintf(yyout,"INT: %s\n", yytext);yylval.number = atoi(yytext); return T_INT; }
\'(\\.|[^'])*\'		   	{fprintf(yyout,"CHARACTER: %s\n", yytext); strcpy(yylval.string, yytext); return CHAR_LITERAL;}
\"(\\.|[^"])*\"		    {fprintf(yyout,"STRING: %s\n", yytext); strcpy(yylval.string, yytext); return STRING_LITERAL;}
"Program"				{fprintf(yyout,"ID: %s\n", yytext); strcpy(yylval.string, yytext); return PROG_ID; }
{LETTER}{ALPHANUMERICAL}*  {fprintf(yyout, "ID: %s\n", yytext); strcpy(yylval.string, yytext); return IDENTIFIER; }
. 						{ fprintf(stdout, "Syntax Error\n"); exit(1);} 
%%
