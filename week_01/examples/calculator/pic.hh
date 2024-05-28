#include <map>
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;

extern map<string,int> table;

union value {
	int a;
	string *b;
};

struct Expression {
	int etype;
	value v;

	Expression(int x = 0) {
		etype = 0;
		v.a = x;
	}

	Expression(string *x) {
		etype = 1;
		v.b = x;
	}

	int get_value() {
		switch (etype)
		{
			case 0:
				return v.a;
			case 1:
				if (table.find(*v.b) != table.end()) {
					return table[*v.b];
				}
				break;
			default:
				break;
		}

		printf("Error: get_value\n");
		exit(1);
	}
};