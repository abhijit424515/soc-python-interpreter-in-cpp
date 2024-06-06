#include "pic.hh"

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
	if (vtype == JSON_STRING) cout << *(string*)value;
	if (vtype == JSON_NUMBER) cout << *(double*)value;
	if (vtype == JSON_BOOL) cout << (*(bool*)value ? "true" : "false");
	if (vtype == JSON_OBJECT) ((JSON*)value)->print(depth);
	if (vtype == JSON_ARRAY) ((JSONArray*)value)->print(depth);
	if (vtype == JSON_NULL) cout << "null";
}

void JSON::print(int depth = 0) {
	string space = "";
	for (int i = 0; i < depth; i++) space += "\t";

	cout << "{" << endl;
	for (auto it = pairs.begin(); it != pairs.end(); it++) {
		cout << space << "\t" << it->first << " : ";
		it->second->print(depth+1);

		if (next(it) == pairs.end()) cout << endl;
		else cout << "," << endl;
	}
	cout << space << "}";
}

JSON::~JSON() {
	for (auto it = pairs.begin(); it != pairs.end(); it++) {
		if (it->second->vtype == JSON_OBJECT) delete (JSON*)it->second->value;
		else if (it->second->vtype == JSON_ARRAY) delete (JSONArray*)it->second->value;
		else delete it->second;
	}
}

void JSONArray::print(int depth = 0) {
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

// ---

map<string,JSONValue*>* append_list_pair(map<string,JSONValue*> *m, pair<string,JSONValue*> *p) {
	if (m == nullptr) m = new map<string,JSONValue*>();
	if (m->find(p->first) != m->end()) {
		cerr << "duplicate key error\n";
		exit(1);
	}
	(*m)[p->first] = p->second;
	return m;
}

JSON* create_obj(map<string,JSONValue*>* pairs) {
	JSON* j = new JSON();
	if (pairs != nullptr) j->pairs = *pairs;
	return j;
}

vector<JSON*>* append_list_obj(vector<JSON*> *l, JSON* o) {
	if (l == nullptr) l = new vector<JSON*>();
	l->push_back(o);
	return l;
}

JSONArray* create_ja(vector<JSON*> *objs) {
	JSONArray *ja = new JSONArray();
	if (objs != nullptr) ja->objects = *objs;
	return ja;
}