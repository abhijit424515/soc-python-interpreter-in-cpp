# Week 01

## What are Compilers and Interpreters ?

A compiler is a program that translates instructions written in a programming language into a machine level program.

An interpreter is a program that executes instructions written in a programming language directly using the base programming language used to create the interpreter without requiring them to have been previously translated into a machine level program.

---

In simpler words, say I want to use `Rust` to write an interpreter for `Python` and a compiler for `Go`. 

- The compiler will take the `Go` code and convert it into machine code, and so the execution speed will be high since you are running machine code during execution.
- The interpreter will take the `Python` code and run it using `Rust`. This way, even simple operations like `add` that could have been done using a couple of ASM instructions are now dependent on the language used to make the interpreter (`Rust` in this case), and so there will be a significant execution overhead. This is why interpreters are generally slower than compilers.

---

Honestly, the line between compilers and interpreters is quite blurry. This is because most languages are not purely compiled or purely interpreted. Improving performance for interpreters always involves going lower level and using more machine code.

For example, `Java` is compiled into `bytecode` which is then interpreted by the `JVM`. So, is `Java` a compiled language or an interpreted language ? The answer is that it is both.

---

## Going Deeper

### Compilers
![Image](./compiler.svg)

### Interpreters
![Image](./interpreter.svg)

Compared to compilers, interpreters have many more possible evaluation strategies (as shown in the diagram) to execute code. 

In our previous example with `Rust`, instead of traversing the abstract syntax tree and executing the code, we could have compiled the `Python` code into `bytecode` and then interpreted it using a virtual machine. This way, we would have a `Python` interpreter that is faster than the one we had before. We could also convert the bytecode into machine code and run it directly, which would make it even faster.

For additional info, checkout `section 3.2` from the `Writing an Interpreter in Go`.

---

## Scanning and Parsing

**Scanning** is the process of breaking the input into small, meaningful units called tokens/lexemes. A token is a sequence of characters that represent a single element of the language, such as a keyword, identifier, or symbol.

For example, the expression `x = 3 + 4` can be broken down into the following tokens:

- `x` (identifier)
- `=` (assignment operator)
- `3` (integer)
- `+` (addition operator)
- `4` (integer)

We use regex to define these tokens and then break down the input code into these tokens either manually (done in the `Writing an Interpreter in Go`) or using a tool like `flex` (what we will be doing) which takes in the regex and automatically creates the `C` program to extract those tokens. 

**Parsing** involves grouping these tokens to form larger structures. 

Here's an example.

```c
main ()
{
  int i,sum;
  sum = 0;
  for (i=1; i<=10; i++)
    sum = sum + i;
  printf("%d\n",sum);
}
```

We can break this down into the following tokens:

`main`, `(`, `)`, `{`, `int`, `i`, `,`, `sum`, `;`, `sum`, `=`, `0`, `;`, `for`, `(`, `i`, `=`, `1`, `;`, `i`, `<=`, `10`, `;`, `i`, `++`, `)`, `sum`, `=`, `sum`, `+`, `i`, `;`, `printf`, `(`, `"%d\n"`, `,`, `sum`, `)`, `;`, `}`

Then, we can group them into the following parse tree

![Image](https://i.imgur.com/ZGJw61y.png)

---

## Flex

`Flex` is a tool that generates programs (having `.l` extension) that perform pattern-matching on text. It is used to generate scanners (lexical analyzers) for programming languages. 

It reads the given input files, or its standard input if no file names are given, for a description of a scanner to generate. The description is in the form of pairs of regular expressions and C code, called `rules`.

It generates as output a C source file named `lex.yy.c`, which defines a routine `yylex()`. This file is compiled and linked with the `-lfl` library to produce an executable. When the executable is run, it analyzes its input for occurrences of the regular expressions. Whenever it finds one, it executes the corresponding C code. 

For an example, checkout the `pic.l` file in the `week_01/examples/calculator/` folder.

In the `rules` section, each line consists of a regex followed by the code to be executed when that regex is matched. The code is enclosed in `{}`.	

## Bison

> Some references may mention Yacc, which is nearly the same as Bison. Bison is a GNU project and has a few extra features compared to Yacc. The syntax is almost the same, so you can use either of them.

`Bison` is a parser generator that converts a grammar description into a `C` program to parse that grammar. It is a `LALR(1)` parser and hence is limited by its rules. One writes context-free grammars or `CFGs` to define the rules in the parser. 

### What is a CFG ?

A context-free grammar is a set of recursive rules used to generate patterns of strings. It is used to define the syntax of programming languages.

CFGs are adequately explained in the `Lex and Yacc` book (link in the parent README file) in Chapter 3 (Using Yacc) from Section 1 (Grammars) to Section 4 (What Yacc Cannot Parse). 

---

For an example, checkout the `pic.y` file in the `week_01/examples/calculator/` folder.

In the `GRAMMAR` section, we define the rules for the parser. Each rule consists of a non-terminal followed by a colon and then the terminals and non-terminals that can be derived from that non-terminal. The code to be executed when that rule is matched is enclosed in `{}`.

If your input is not in the language defined by the grammar, the parser will throw a `syntax error`.

In the `week_01/examples/calculator` program, we have defined a simple calculator that can perform addition, subtraction, multiplication, and division using variables (see the sample input).

However, in the `week_01/examples/json` program, we have not specified any actions in the `pic.y` file. So, if your input is in the language defined by the grammar, the parser will not throw any error and no output will be generated (exit code 0).

---

## Examples

2 examples have been provided in the `week_01/examples` folder, namely `calculator` and `json`. For each of them, there is a `Makefile` that can be used to compile the program.

After changing to the respective directory, run `make` to compile the program, which produces the `runme` executable. Then, run `./runme < input` to run the program, using the `input` file as input to the program.

Feel free to modify the `input` file to test the program with different inputs.

You can also run the `calculator` program without the `< input` to run the program in interactive mode. Use `Ctrl+D` to exit the program.

## Assignment

- If you haven't done a course on `Theory of Computation`, read the `Lex and Yacc` book (link in the parent README file) Chapter 3 (Using Yacc) from Section 1 (Grammars) to Section 4 (What Yacc Cannot Parse) to understand CFGs. 
- Understand the `week_01/examples/calculator` and `week_01/examples/json` programs, and write the actions for the `json` program. You will need to create approprate classes like `JSONArray`, `JSONObject`, `JSONString`, `JSONNumber`, etc. and then create a `JSON` object that can be used to represent the JSON input.
- Using the given example programs, create a parser for CSV files (having a header row on top). Start with the lexer and then move on to the parser.

### Submission

TBA