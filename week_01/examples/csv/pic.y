%{
		#include "pic.cc"
		extern "C" void yyerror(const char *s);
		extern int yylex(void);
%}

%union{
	string *name;
	CSVElem *elem;
	VecWrapper* vec;
	VecVecWrapper* vecvec;
	Column* col;
	CSV* csv;
}

%token TRUE_CONST FALSE_CONST NULL_CONST COMMA INT_CONST FLT_CONST STR_CONST NEWLINE
%type <name> INT_CONST FLT_CONST STR_CONST
%type <elem> name literal
%type <csv> header
%type <vecvec> rows
%type <vec> array name_array

%start program
%%

/* GRAMMAR */
/**
 * Assuming empty file to be valid
 * this is not a very performant implementation; so feel free to write a more optimal one :)
 */

program
	: optional_newline											{ cout << "Empty file" << endl; }
	| header optional_newline									{ $1->print(); delete $1; }
	| header NEWLINE rows optional_newline						{ $1->process_entries($3); $1->print();	delete $1; }
;

header
	: name_array												{ $$ = init_csv($1); }
;

name_array
	: name														{ $$ = append_list_obj(nullptr, $1); }
	| name_array COMMA name										{ $$ = append_list_obj($1, $3); }	
;

rows
	: array														{ $$ = append_list_vec(nullptr, $1); }
	| rows NEWLINE array										{ $$ = append_list_vec($1, $3); }
;

array
	: literal													{ $$ = append_list_obj(nullptr, $1); }
	| array COMMA literal										{ $$ = append_list_obj($1, $3); }
;

literal
	: INT_CONST													{ $$ = new CSVElem(new int(atoi($1->c_str())), CSV_INT); }
	| FLT_CONST													{ $$ = new CSVElem(new double(atof($1->c_str())), CSV_FLT); }
	| STR_CONST													{ $$ = new CSVElem($1, CSV_STRING); }
	| TRUE_CONST												{ $$ = new CSVElem(new bool(true), CSV_BOOL); }
	| FALSE_CONST												{ $$ = new CSVElem(new bool(false), CSV_BOOL); }
	| NULL_CONST 												{ $$ = new CSVElem(nullptr, CSV_NULL);}
;

name
	: STR_CONST													{ $$ = new CSVElem($1, CSV_STRING); }
;

optional_newline
	: NEWLINE
	| %empty
;

%%
/* ADDITIONAL C CODE */

int main() {
	yyparse();
	return 0;
}