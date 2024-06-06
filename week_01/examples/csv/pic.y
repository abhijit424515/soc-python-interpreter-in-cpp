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

%token TRUE_CONST FALSE_CONST NULL_CONST COMMA INT_CONST FLT_CONST STR_CONST
%type <name> INT_CONST FLT_CONST STR_CONST
%type <elem> name literal
%type <csv> header
%type <vecvec> tail
%type <vec> array name_array

%start program
%%

/* GRAMMAR */
/**
 * Assuming empty file to be valid
 * this is not very performant code; feel free to write optimal code :)
 */

program
	: %empty						{cout<<"Empty file"<<endl;}
	| header						{$1->print(); delete $1;}
	| header tail					{	
										$1->process_entries($2);
										$1->print();
										delete $1;
									}
;

header
	: name_array					{$$ = init_csv($1);}

name_array
	: name							{$$ = append_list_obj(nullptr, $1);}
	| name_array COMMA name			{$$ = append_list_obj($1, $3);}	

tail
	: array							{$$ = append_list_vec(nullptr, $1);}
	| tail array					{$$ = append_list_vec($1, $2);}

array
	: %empty						{$$ = append_list_obj(nullptr, new CSVElem(nullptr,CSV_NULL));}
	| array COMMA literal			{$$ = append_list_obj($1, $3);}
	| array COMMA					{$$ = append_list_obj($1, new CSVElem(nullptr,CSV_NULL));}

literal
	: INT_CONST						{$$ = new CSVElem($1, CSV_NUMBER);}
	| FLT_CONST						{$$ = new CSVElem($1, CSV_NUMBER);}
	| STR_CONST						{$$ = new CSVElem($1, CSV_STRING);}
	| TRUE_CONST					{$$ = new CSVElem(new bool(true), CSV_BOOL);}
	| FALSE_CONST					{$$ = new CSVElem(new bool(false), CSV_BOOL);}
	| NULL_CONST 					{$$ = new CSVElem(nullptr, CSV_NULL);}

name
	: STR_CONST						{$$ = new CSVElem($1, CSV_STRING);}
%%
/* ADDITIONAL C CODE */

int main(){
  yyparse();
  return 0;
}