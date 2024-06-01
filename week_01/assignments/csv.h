#include <bits/stdc++.h>
using namespace std;

enum CSVType {
	CSV_STRING,
	CSV_NUMBER,
	CSV_BOOL,
	CSV_NULL
};

struct Column {
	CSVType vtype;
	string name;
	vector<void*> values;

	Column() {}
	Column(const Column& other) : vtype(other.vtype), name(other.name), values(other.values) {}
};

struct CSV {
	vector<Column> columns;

	CSV() {}
	CSV(const CSV& other) : columns(other.columns) {}

	void print() {
		for (int i = 0; i < columns.size(); i++) {
			cout << columns[i].name << " ";
		}
		cout << endl;
		for (int i = 0; i < columns[0].values.size(); i++) {
			for (int j = 0; j < columns.size(); j++) {
				switch (columns[j].vtype) {
					case CSV_STRING:
						cout << *(string*)columns[j].values[i] << " ";
						break;
					case CSV_NUMBER:
						cout << *(double*)columns[j].values[i] << " ";
						break;
					case CSV_BOOL:
						cout << *(bool*)columns[j].values[i] << " ";
						break;
					case CSV_NULL:
						cout << "null ";
						break;
				}
			}
			cout << endl;
		}
	}
};