%{
    #include "pic.cc"
    extern "C" void yyerror(const char *s);
    extern int yylex(void);
%}

%union{
	string *name;	
}

%token TRUE_CONST FALSE_CONST NULL_CONST LCB RCB LSB RSB COMMA COLON INT_CONST FLT_CONST STR_CONST
%type <name> INT_CONST FLT_CONST STR_CONST

%start program
%%

/* GRAMMAR */

program
	: array
	| object
;

array
	: LSB objects RSB
	| LSB RSB
;

objects
	: objects COMMA object
	| object
;

object
	: LCB pairs RCB
	| LCB RCB
;

pairs
	: pairs COMMA pair
	| pair
;

pair
	: STR_CONST COLON value
;

value
	: object
	| array
	| STR_CONST
	| INT_CONST
	| FLT_CONST
	| TRUE_CONST
	| FALSE_CONST
	| NULL_CONST
;

%%

/* ADDITIONAL C CODE */

int main(){
  yyparse();
  return 0;
}