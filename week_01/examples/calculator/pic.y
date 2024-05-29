%{
    #include "pic.cc"
    extern "C" void yyerror(const char *s);
    extern int yylex(void);
		extern map<string, double> table;
%}

%union{
	string *name;	
	Expression *exp;
}

%token INT_CONST FLT_CONST NAME

%left '+' '-'
%left '*' '/'
%right Uminus

%type <name> INT_CONST FLT_CONST NAME
%type <exp> expression

%start program
%%

/* GRAMMAR */

program
	:	stmt_list
;

stmt_list
	:	stmt_list stmt
	|	stmt
;

stmt
	:	NAME '=' expression ';'								{ double x = $3->get_value(); table[*($1)] = x; }
	| expression ';'												{ double x = $1->get_value(); cout << x << endl; }
;

expression
	: expression '+' expression							{ double x1 = $1->get_value(); double x2 = $3->get_value(); $$ = new Expression(x1 + x2); }
	| expression '*' expression							{ double x1 = $1->get_value(); double x2 = $3->get_value(); $$ = new Expression(x1 * x2); }
	| expression '/' expression							{ double x1 = $1->get_value(); double x2 = $3->get_value(); $$ = new Expression(x1 / x2); }
	| expression '-' expression							{ double x1 = $1->get_value(); double x2 = $3->get_value(); $$ = new Expression(x1 - x2); }
	| '-' expression %prec Uminus						{ double x = $2->get_value(); $$ = new Expression(-x); }
	| INT_CONST															{ $$ = new Expression(atoi($1->c_str())); }
	| FLT_CONST															{ $$ = new Expression(atof($1->c_str())); }
	| NAME																	{ $$ = new Expression($1); }
;

%%

/* ADDITIONAL C CODE */

int main(){
  yyparse();
  return 0;
}