/* PROLOGUE */

%{
	#include "pic.hh"
	#include "parse.tab.h"
	using namespace std;
%}

/* DEFINITIONS */

/* yywrap handles the end-of-input logic, if noyywrap is used, program exits on end-of-file (EOF) */
%option noyywrap 

/* DEFINITIONS */

digit                       [0-9]
fraction                    ([0-9]*\.[0-9]+|[0-9]+\.[0-9]*)
ws													[ \t\n]*
operator										[-+*/=;]
letter                      [a-zA-Z_]

/* RULES */

%%

{digit}+										{ yylval.name = new string(yytext); return INT_CONST; }
{fraction}									{ yylval.name = new string(yytext); return FLT_CONST; }
{operator}									{ return yytext[0]; }
{letter}({letter}|{digit})* { yylval.name = new string(yytext); return NAME; }

{ws}       									; /* Ignore spaces */
.         									{ fprintf(stderr, "unknown_token: %d\n", yytext[0]); exit(1); }
