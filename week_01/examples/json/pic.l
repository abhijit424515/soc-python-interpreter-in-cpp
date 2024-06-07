%{
	#include "pic.hh"
	#include "parse.tab.h"
	using namespace std;
%}

/* DEFINITIONS */

/* yywrap handles the end-of-input logic, if noyywrap is used, program exits on end-of-file (EOF) */
%option noyywrap 

digit                       [0-9]
fraction                    ([0-9]*\.[0-9]+|[0-9]+\.[0-9]*)
ws							[ \t\n]*
letter                      [a-zA-Z_]

/* RULES */
%%

true						{ return TRUE_CONST; }
false						{ return FALSE_CONST; }
null						{ return NULL_CONST; }

\{							{ return LCB; }	
\}							{ return RCB; }
\[							{ return LSB; }
\]							{ return RSB; }
,							{ return COMMA; }
:							{ return COLON; }

-?{digit}+					{ yylval.name = new string(yytext); return INT_CONST; }
-?{fraction}				{ yylval.name = new string(yytext); return FLT_CONST; }
\"([^\"]*)\"                { yylval.name = new string(yytext); return STR_CONST; }

{ws}       					; /* Ignore spaces */
.         					{ fprintf(stderr, "unknown_token: %d\n", yytext[0]); exit(1); }
