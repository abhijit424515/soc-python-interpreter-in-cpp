#include "pic.hh"

string delim = ",";

CSV* init_csv(VecWrapper* header) {
	if (header==nullptr) {
		cerr << "Header is null" << endl;
		exit(1);
	}
	CSV *csv = new CSV();
	for (CSVElem* elem: header->vec) {
		Column* col = new Column();
		col->vtype = CSV_NULL; // i will use CSV_NULL for the column whose type is currently unknown
		col->name = *(string*)elem->value;
		csv->columns.push_back(col);
	}
	return csv;
}

VecWrapper* append_list_obj(VecWrapper* head, CSVElem* new_elem) {
	if (head == nullptr) head = new VecWrapper();
	head->vec.push_back(new_elem);
	return head;
}

VecVecWrapper* append_list_vec(VecVecWrapper* m, VecWrapper* p) {
	if (m == nullptr) m = new VecVecWrapper();
	m->vec.push_back(p);
	return m;
}

// ---

void CSV::process_entries(VecVecWrapper* entries) {
	if (entries == nullptr || entries->vec.size() == 0) return;
	for (int i=0; i < entries->vec[0]->vec.size(); i++) {
		columns[i]->vtype = entries->vec[0]->vec[i]->vtype;
	}
	for (VecWrapper* row: entries->vec) {
		if (row->vec.size() != columns.size()) {
			cerr << row->vec.size() << " " << columns.size() << endl;
			cerr << "Row size does not match header size" << endl;
			exit(1);
		}
		for (int i=0; i < row->vec.size(); i++) {
			CSVElem* elem = row->vec[i];
			Column* col = columns[i];
			// cout << elem->vtype << " " << col->vtype << " ";
			if (col->vtype != elem->vtype) {
				cerr << "Type mismatch in column " << col->name << endl;
				exit(1);
			}
			// cout << col->vtype << endl;
			col->values.push_back(elem->value);
		}
	}
}

void CSV::print() {
	for (int i = 0; i < columns.size(); i++) {
		cout << columns[i]->name;
		if (i != columns.size()-1) cout << delim;
	}
	cout << endl;
	for (int i = 0; i < columns[0]->values.size(); i++) {
		for (int j = 0; j < columns.size(); j++) {
			switch (columns[j]->vtype) {
				case CSV_STRING:
					cout << *(string*) (columns[j]->values[i]);
					break;
				case CSV_INT:
					cout << *(int*) (columns[j]->values[i]);
					break;
				case CSV_FLT:
					cout << *(double*) (columns[j]->values[i]);
					break;
				case CSV_BOOL:
					cout << *(bool*) (columns[j]->values[i]) ? "true" : "false";
					break;
				case CSV_NULL:
					cout << "null";
					break;
			}
			if (j != columns.size()-1) cout << delim;
		}
		cout << endl;
	}
}