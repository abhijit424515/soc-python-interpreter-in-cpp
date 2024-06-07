%{
	#include "pic.hh"
	#include "parse.tab.h"
	using namespace std;
%}

/* DEFINITIONS */

/* yywrap handles the end-of-input logic, if noyywrap is used, program exits on end-of-file (EOF) */
%option noyywrap 

digit									[0-9]
fraction                    			(-?[0-9]*\.[0-9]+|[0-9]+\.[0-9]*)
ws										[ \t\n]*
letter                      			[a-zA-Z_]

/* RULES */

/**
 * Some Assumptions: 
 * Only Commas Allowed as Delimiters
 * Only Newline Allowed as Statement Delimiter
 * Double Quotes if using spaces or special characters in strings
 * There can be empty entries
 * Header is compulsorily the first line 
 */
%%

true									{ return TRUE_CONST; }
false									{ return FALSE_CONST; }
null									{ return NULL_CONST; }

,										{ return COMMA; }

-?{digit}+								{ yylval.name = new string(yytext); return INT_CONST; }
{fraction}								{ yylval.name = new string(yytext); return FLT_CONST; }
{letter}({letter}|{digit})*				{ yylval.name = new string(yytext); return STR_CONST; }
\"([^\"]*)\"                			{ yylval.name = new string(yytext); return STR_CONST; }

\n      	                       		{ return NEWLINE;} 
.         								{ fprintf(stderr, "unknown_token: %d\n", yytext[0]); exit(1); }
