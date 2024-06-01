#include <bits/stdc++.h>
using namespace std;

enum JSONType {
	JSON_STRING,
	JSON_NUMBER,
	JSON_BOOL,
	JSON_NULL,
	JSON_OBJECT,
	JSON_ARRAY,
};

struct JSON;
struct JSONArray;

struct JSONValue {
	JSONType vtype;
	void *value;

	JSONValue(string x) {
		vtype = JSON_STRING;
		value = new string(x);
	}
	JSONValue(const char *x) {
		vtype = JSON_STRING;
		value = new string(x);
	}
	JSONValue(double x) {
		vtype = JSON_NUMBER;
		value = new double(x);
	}
	JSONValue(int x) {
		vtype = JSON_NUMBER;
		value = new int(x);
	}
	JSONValue(bool x) {
		vtype = JSON_BOOL;
		value = new bool(x);
	}
	JSONValue(nullptr_t) {
		vtype = JSON_NULL;
		value = nullptr;
	}
	JSONValue(const JSON& x);
	JSONValue(const JSONArray& x);
  ~JSONValue();

	void print(int depth);
};

struct JSON {
	map<string,JSONValue*> pairs;

	JSON() {}
	JSON(const JSON& other) : pairs(other.pairs) {}
	~JSON();

	void print(int depth = 0) {
		string space = "";
		for (int i = 0; i < depth; i++) space += "\t";

		cout << "{" << endl;
		for (auto it = pairs.begin(); it != pairs.end(); it++) {
			cout << space << "\t\"" << it->first << "\" : ";
			it->second->print(depth+1);

			if (next(it) == pairs.end()) cout << endl;
			else cout << "," << endl;
		}
		cout << space << "}";
	}
};

struct JSONArray {
	vector<JSON*> objects;

	JSONArray() {}
	JSONArray(const JSONArray& other) : objects(other.objects) {}
	~JSONArray() {
		for (int i = 0; i < objects.size(); i++) delete objects[i];
	}

	void print(int depth = 0) {
		string space = "";
		for (int i = 0; i < depth; i++) space += "\t";

		cout << "[" << endl;
		for (int i = 0; i < objects.size(); i++) {
			cout << space << "\t";
			objects[i]->print(depth+1);
			
			if (i == objects.size()-1) cout << endl;
			else cout << "," << endl;
		}
		cout << space << "]";
	}
};

// --- fixing forward declaration problems 😛

JSONValue::JSONValue(const JSON& x) {
	vtype = JSON_OBJECT;
	value = new JSON(x);
}

JSONValue::JSONValue(const JSONArray& x) {
	vtype = JSON_ARRAY;
	value = new JSONArray(x);
}

JSONValue::~JSONValue() {
	if (vtype == JSON_STRING) delete (string*)value;
	if (vtype == JSON_NUMBER) delete (double*)value;
	if (vtype == JSON_BOOL) delete (bool*)value;
	if (vtype == JSON_OBJECT) delete (JSON*)value;
	if (vtype == JSON_ARRAY) delete (JSONArray*)value;
}

void JSONValue::print(int depth = 0) {
	if (vtype == JSON_STRING) cout << "\"" << *(string*)value << "\"";
	if (vtype == JSON_NUMBER) cout << *(double*)value;
	if (vtype == JSON_BOOL) cout << (*(bool*)value ? "true" : "false");
	if (vtype == JSON_OBJECT) ((JSON*)value)->print(depth);
	if (vtype == JSON_ARRAY) ((JSONArray*)value)->print(depth);
	if (vtype == JSON_NULL) cout << "null";
}

JSON::~JSON() {
	for (auto it = pairs.begin(); it != pairs.end(); it++) {
		if (it->second->vtype == JSON_OBJECT) delete (JSON*)it->second->value;
		else if (it->second->vtype == JSON_ARRAY) delete (JSONArray*)it->second->value;
		else delete it->second;
	}
}