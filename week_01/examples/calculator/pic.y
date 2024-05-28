%{
    #include "pic.cc"
    extern "C" void yyerror(const char *s);
    extern int yylex(void);
		extern map<string, int> table;
%}

%union{
	string *name;	
	Expression *exp;
}

%token INT_CONST NAME

%left '+' '-'
%left '*' '/'
%right Uminus

%type <name> INT_CONST NAME
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
	:	NAME '=' expression ';'								{ int x = $3->get_value(); table[*($1)] = x; }
	| expression ';'												{ int x = $1->get_value(); cout << x << endl; }
;

expression
	: expression '+' expression							{ int x1 = $1->get_value(); int x2 = $3->get_value(); $$ = new Expression(x1 + x2); }
	| expression '*' expression							{ int x1 = $1->get_value(); int x2 = $3->get_value(); $$ = new Expression(x1 * x2); }
	| expression '/' expression							{ int x1 = $1->get_value(); int x2 = $3->get_value(); $$ = new Expression(x1 / x2); }
	| expression '-' expression							{ int x1 = $1->get_value(); int x2 = $3->get_value(); $$ = new Expression(x1 - x2); }
	| '-' expression %prec Uminus						{ int x = $2->get_value(); $$ = new Expression(-x); }
	| INT_CONST															{ $$ = new Expression(atoi($1->c_str())); }
	| NAME																	{ $$ = new Expression($1); }
;

%%

/* ADDITIONAL C CODE */

int main(){
  yyparse();
  return 0;
}