# The Monkey Programming Language

## Introduction

The `Monkey` programming language is a simple language with the following syntax:

- It has 3 primary data types: `int`, `bool`, and `string`.
- It has the following operators: `+`, `-`, `*`, `/`, `==`, `!=`, `<`, `>`, `<=`, `>=`, `!`, `&&`, `||`.
- It has the following control structures: `if`, `else`, `for`, `while`.
- It has the following data structures: `array` and `hash`.

```js
let pass = fn(x) {
	if (x <= 30) {
		return true;
	} else {
		return false;
	}
};
let result = 10 * (20 / 2);
let passed = pass(result);

let myArray = [1, 2, 3, 4, 5];
let thorsten = {"name": "Thorsten", "age": 28};

let num = myArray[2];
let name = thorsten["name"];
```

---

- It has function literals and function calls. Implicit return values are also possible, like `fn (x) { x + 2; }` where explicitely using `return` is not needed. 
- Functions can be called recursively, and support higher order functions, i.e. functions that take other functions as arguments.

```js
let twice = fn(f, x) {
  return f(f(x));
};

let addTwo = fn(x) {
  return x + 2;
};

twice(addTwo, 2); // => 6
```

---

## The Object Data Model

The `Monkey` programming language has a simple object model. Everything in `Monkey` is an object, and objects can have methods. 

Let's take the example of a `function`. A function in `Monkey` is an object that has a `body` and a `context`. The `body` is the code that the function executes, and the `context` is the environment in which the function was defined. 

```js
let newAdder = fn(x) {
  return fn(y) { x + y; };
};

let addTwo = newAdder(2);
addTwo(3); // => 5
```

A representation of an object struct in C++ would look like this:

```cpp
enum ObjectType {
  INTEGER,
  BOOLEAN,
  STRING,
  NULL,
  FUNCTION,
  ARRAY,
  HASH
};

struct Object {
	ObjectType type;
	void* value;
	virtual void inspect() = 0;
};
```

A function object would be derived from the `Object` struct as follows:

```cpp
struct Function: public Object {
	std::vector<string> parameters;
	std::vector<Statement*> body;
	std::map<string,Object*> *env;

	void inspect() {
		std::cout << "fn(";
		for (int i = 0; i < parameters.size(); i++) {
    		std::cout << parameters[i];
    		if (i != parameters.size() - 1)
    			std::cout << ", ";
		}
		std::cout << ") { ";
		for (int i = 0; i < body.size(); i++)
    		std::cout << body[i]->print();
		std::cout << " }\n";
	}
};
```

To account for varying environments (aka scopes), we need a stack of environments to keep track of the current environment. 

```cpp
vector<map<string,Object*>*> envStack;
```

Initially, we will add an empty environment to the stack to serve as the global scope. Any additional scopes will be created in the heap, and their pointers will be added to the stack and also saved in the required `Object` environment (like in `Function`).

### Sidenote

Since datatypes are not explicitly defined in `Monkey`, type validation in cases like

```js
let twice = fn(f, x) {
  return f(f(x));
};
```

is to be performed during runtime. This is a tradeoff for the simplicity of the language.

---

## Read Eval Print Loop (REPL)

TBD