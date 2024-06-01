#include "json.h"

int main() {
	JSON* jsonObject = new JSON();

	jsonObject->pairs["name"] = new JSONValue("John Doe");
	jsonObject->pairs["age"] = new JSONValue(30);
	jsonObject->pairs["is_student"] = new JSONValue(true);

	JSONArray* jsonArray = new JSONArray();

	JSON* object1 = new JSON();
	object1->pairs["id"] = new JSONValue(1);
	object1->pairs["name"] = new JSONValue("Alice");

	JSON* object2 = new JSON();
	object2->pairs["id"] = new JSONValue(2);
	object2->pairs["name"] = new JSONValue("Bob");

	jsonArray->objects.push_back(object1);
	jsonArray->objects.push_back(object2);
	jsonObject->pairs["friends"] = new JSONValue(*jsonArray);

	jsonObject->print();
	delete jsonObject;
}
