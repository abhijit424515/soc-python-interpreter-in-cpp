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

<div style="display: flex; gap: 3rem; width: 100%; justify-content: center; margin-bottom: 2rem">
  <div style="display: flex; flex-direction: column; align-items: center">
		<h3>Compilers</h3>
    <img src="./compiler.svg" />
  </div>
	<div style="display: flex; flex-direction: column; align-items: center">
  	<h3>Interpreters</h3>
  	<img src="./interpreter.svg" />
  </div>
</div>

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

`Flex` is a tool that generates programs that perform pattern-matching on text. It is used to generate scanners (lexical analyzers) for programming languages.

