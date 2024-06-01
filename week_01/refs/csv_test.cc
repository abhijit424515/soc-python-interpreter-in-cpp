#include "csv.h"

int main() {
	CSV* csv = new CSV();

	Column* column1 = new Column();
	column1->vtype = CSV_STRING;
	column1->name = "Name";
	column1->values.push_back(new string("John"));
	column1->values.push_back(new string("Alice"));

	Column* column2 = new Column();
	column2->vtype = CSV_NUMBER;
	column2->name = "Age";
	column2->values.push_back(new double(30));
	column2->values.push_back(new double(25));

	Column* column3 = new Column();
	column3->vtype = CSV_BOOL;
	column3->name = "IsStudent";
	column3->values.push_back(new bool(true));
	column3->values.push_back(new bool(false));
	
	csv->columns.push_back(column1);
	csv->columns.push_back(column2);
	csv->columns.push_back(column3);

	csv->print();
	delete csv;
}
