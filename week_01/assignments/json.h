#include <bits/stdc++.h>
using namespace std;

struct JSON;

struct JSONArray {
	vector<JSON> objects;

	JSONArray() {}
	JSONArray(const JSONArray& other) : objects(other.objects) {}

	void print() {
		cout << "[" << endl;
		for (int i = 0; i < objects.size(); i++) {
			objects[i].print();
			cout << ", " << endl;
		}
		cout << "]" << endl;
	}
};

enum JSONType {
	JSON_STRING,
	JSON_NUMBER,
	JSON_BOOL,
	JSON_OBJECT,
	JSON_ARRAY,
	JSON_NULL
};

struct JSONValue {
	JSONType vtype;
	void *value;

	JSONValue(string x) {
		vtype = JSON_STRING;
		value = new string(x);
	}

	JSONValue(double x) {
		vtype = JSON_NUMBER;
		value = new double(x);
	}

	JSONValue(bool x) {
		vtype = JSON_BOOL;
		value = new bool(x);
	}

	JSONValue(const JSON& x) {
		vtype = JSON_OBJECT;
		value = new JSON(x);
	}

	JSONValue(const JSONArray& x) {
		vtype = JSON_ARRAY;
		value = new JSONArray(x);
	}

	JSONValue(nullptr_t) {
		vtype = JSON_NULL;
		value = nullptr;
	}

  ~JSONValue() {
		if (vtype == JSON_STRING) delete (string*)value;
		if (vtype == JSON_NUMBER) delete (double*)value;
		if (vtype == JSON_BOOL) delete (bool*)value;
		if (vtype == JSON_OBJECT) delete (JSON*)value;
		if (vtype == JSON_ARRAY) delete (JSONArray*)value;
	}

	void print() {
		if (vtype == JSON_STRING) cout << *(string*)value;
		if (vtype == JSON_NUMBER) cout << *(double*)value;
		if (vtype == JSON_BOOL) cout << *(bool*)value;
		if (vtype == JSON_OBJECT) ((JSON*)value)->print();
		if (vtype == JSON_ARRAY) ((JSONArray*)value)->print();
		if (vtype == JSON_NULL) cout << "null";
	}
};

struct JSON {
	map<string,JSONValue> pairs;

	JSON() {}
	JSON(const JSON& other) : pairs(other.pairs) {}

	void print() {
		cout << "{" << endl;
		for (auto it = pairs.begin(); it != pairs.end(); it++) {
			cout << it->first << ": ";
			it->second.print();
			cout << ", " << endl;
		}
		cout << "}";
	}
};