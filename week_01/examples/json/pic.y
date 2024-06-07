%{
	#include "pic.cc"
	extern "C" void yyerror(const char *s);
	extern int yylex(void);
%}

%union{
	string *name;
	JSONValue *jv;
	pair<string,JSONValue*> *p;
	map<string,JSONValue*> *o;
	JSON *j;
	vector<JSON*> *jl;
	JSONArray *ja;
}

%token TRUE_CONST FALSE_CONST NULL_CONST LCB RCB LSB RSB COMMA COLON INT_CONST FLT_CONST STR_CONST
%type <name> INT_CONST FLT_CONST STR_CONST
%type <jv> value
%type <p> pair
%type <o> pairs 
%type <j> object
%type <jl> objects
%type <ja> array

%start program
%%

/* GRAMMAR */

program
	: array										{ $1->print(); }
	| object									{ $1->print(); }
;

array
	: LSB objects RSB							{ $$ = create_ja($2); }
	| LSB RSB									{ $$ = create_ja(nullptr); }
;

objects
	: objects COMMA object						{ $$ = append_list_obj($1, $3); }
	| object									{ $$ = append_list_obj(nullptr, $1); }
;

object
	: LCB pairs RCB								{ $$ = create_obj($2); }
	| LCB RCB									{ $$ = create_obj(nullptr); }
;

pairs
	: pairs COMMA pair							{ $$ = append_list_pair($1, $3); }
	| pair										{ $$ = append_list_pair(nullptr, $1); }
;

pair
	: STR_CONST COLON value						{ $$ = new pair<string,JSONValue*>(*($1), $3); }
;

value
	: object									{ $$ = new JSONValue(*($1)); }
	| array										{ $$ = new JSONValue(*($1)); }
	| STR_CONST									{ $$ = new JSONValue(*($1)); }
	| INT_CONST									{ $$ = new JSONValue(atoi($1->c_str())); }
	| FLT_CONST									{ $$ = new JSONValue(atof($1->c_str())); }
	| TRUE_CONST								{ $$ = new JSONValue(true); }
	| FALSE_CONST								{ $$ = new JSONValue(false); }
	| NULL_CONST								{ $$ = new JSONValue(nullptr); }
;

%%

/* ADDITIONAL C CODE */

int main(){
  yyparse();
  return 0;
}