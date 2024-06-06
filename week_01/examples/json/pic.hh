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

	void print(int depth);
};

struct JSONArray {
	vector<JSON*> objects;

	JSONArray() {}
	JSONArray(const JSONArray& other) : objects(other.objects) {}
	~JSONArray() {
		for (int i = 0; i < objects.size(); i++) delete objects[i];
	}

	void print(int depth);
};

// ---

map<string,JSONValue*>* append_list_pair(map<string,JSONValue*> *m, pair<string,JSONValue*> *p);
JSON* create_obj(map<string,JSONValue*>* pairs);
vector<JSON*>* append_list_obj(vector<JSON*> *l, JSON* o);
JSONArray* create_ja(vector<JSON*> *objs);