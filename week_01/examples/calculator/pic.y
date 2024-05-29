%{
		// Declarations (C++ code)

    #include "pic.cc"
    extern "C" void yyerror(const char *s);
    extern int yylex(void);
		extern map<string, double> table;
%}

%union{
	string *name;	
	Expression *exp;
}

%token INT_CONST FLT_CONST NAME 					// Token declarations (lexer uses these declarations to return tokens)

%left '+' '-' 														// Left associative operators '+' and '-'
%left '*' '/' 														// Left associative operators '*' and '/'
%right Uminus 														// Right associative unary minus operator

%type <name> INT_CONST FLT_CONST NAME 		// Declare token types to be of type *string
%type <exp> expression 										// Declare the expression non-terminal to be of type *Expression

%start program 														// Starting rule for the grammar
%%

/* GRAMMAR */

program
	:	stmt_list															// A program consists of a list of statements
;

stmt_list
	:	stmt_list stmt												// A statement list can be another statement list followed by a statement
	|	stmt																	// Or just a single statement
;

stmt
	:	NAME '=' expression ';'								{ double x = $3->get_value(); table[*($1)] = x; }		// Assignment statement
	| expression ';'												{ double x = $1->get_value(); cout << x << endl; } 	// Expression statement: just evaluate the expression and print its value
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

int main() { // here's our main function, where it all starts
  yyparse();
  return 0;
}