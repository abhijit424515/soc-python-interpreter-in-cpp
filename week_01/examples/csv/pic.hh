#include <bits/stdc++.h>
using namespace std;

enum CSVType {
	CSV_STRING,
	CSV_INT,
	CSV_FLT,
	CSV_BOOL,
	CSV_NULL
};

struct CSVElem{
	CSVType vtype;
	void *value;
	CSVElem(void* value, CSVType vtype) : value(value), vtype(vtype) {}
	~CSVElem() {} // memory management of pointer is handled by the Column
};

struct VecWrapper{
	vector<CSVElem*> vec;
	VecWrapper() {}
	VecWrapper(const VecWrapper& other) : vec(other.vec) {}
	~VecWrapper() {
		for (int i = 0; i < vec.size(); i++) delete vec[i];
	}
};

struct VecVecWrapper{
	vector<VecWrapper*> vec;
	VecVecWrapper() {}
	VecVecWrapper(const VecVecWrapper& other) : vec(other.vec) {}
	~VecVecWrapper() {
		for (int i = 0; i < vec.size(); i++) delete vec[i];
	}
};

struct Column {
	CSVType vtype;
	string name;
	vector<void*> values;

	Column() {}
	Column(const Column& other) : vtype(other.vtype), name(other.name), values(other.values) {}
	~Column() {
		for (int i = 0; i < values.size(); i++) {
			switch (vtype) {
				case CSV_STRING:
					delete (string*)values[i];
					break;
				case CSV_INT:
					delete (int*)values[i];
					break;
				case CSV_FLT:
					delete (double*)values[i];
					break;
				case CSV_BOOL:
					delete (bool*)values[i];
					break;
				case CSV_NULL:
					break;
			}
		}
	}
};

struct CSV {
	vector<Column*> columns;

	CSV() {}
	CSV(const CSV& other) : columns(other.columns) {}
	~CSV() {
		for (Column* c : columns) delete c;
	}

	void process_entries(VecVecWrapper* entries);
	void print();
};

CSV* init_csv(VecWrapper*);
VecWrapper* append_list_obj(VecWrapper* head, CSVElem* new_elem);
VecVecWrapper* append_list_vec(VecVecWrapper* m, VecWrapper* p);