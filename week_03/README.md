# Week 03

Unfortunately, the previous assignment was not well thought out. The issue was that `bison` (the parser-generator that we are using) relies on a Context-Free grammar, which is not the case for indentation based formats like YAML which use Context-Sensitive grammars. It is still theoretically possible to parse YAML with `bison` by creating a CFG superset of the CSG, but it is not a trivial task, and is not the spirit of this SoC. Parsing is only the beginning, and we have much more to do to execute the input code. 

As communicated, because of this blunder, only those mentees who have simply ignored the assignment and not even attempted it are not allowed to continue as `official mentees`, and the rest of you can continue under the benefit of doubt.

To not land into such programs in our process of learning and actually understanding the workings of an interpreter, instead of creating an interpreter for Python, we will create one for a simpler language called the `Monkey` programming language (defined in the `Writing an Interpreter in Go` book in the `Introduction` part before the starting chapter). 

The language is simple and easy to understand, and uses semicolon instead of the newline character and brackets instead of indentation. 

---

## Assignment

Since the book is meant to write the interpreter in `Go`, this week's assignment is to understand the description and syntax of the `Monkey` programming language, and to write a parser for the same in `C++` using `flex` and `bison`, and using them to generate Abstract Syntax Trees (ASTs). 

1. The list of tokens is already described in the book in Chapter 1, however instead of using a scanner generator like `flex`, the author has manually written the scanner in `Go`. It is optional to read through that manual scanning code if you know the `Go` language to gain a better perspective to the workings of a scanner.

2. The 2nd Chapter of the book describes the process of parsing and the notion of an Abstract Syntax Tree (AST). You can directly use the given `Go` code (the structs and their methods) to create the equivalent `C++` code, but it is recommended to understand the need and the structure of ASTs, and create the structs and their methods by yourself step-by-step. 

3. Since the author has manually written the parser too, you need to write your own grammar for the `Monkey` language. Here is a good reference [SCLP](https://www.cse.iitb.ac.in/~uday/sclp-web/). This is the website of our Compilers lab course, which also contains the grammar for `C`. You can go through it alongwith Chapter 2 of the `Writing an Interpreter in Go` book to understand how to write a grammar for the `Monkey` language yourself. **Currently, we are only expecting a basic grammar

---

## [The Monkey Programming Language](./monkey.md)

Repositories for additional open-source implementations of the Monkey programming language are listed on the [official website](https://monkeylang.org/). **Do check them out for hints**.

---

## Submission

**From this week onwards, the assignments will follow a sequential pattern, and will be cumulative in nature. This means that the assignments will build on top of each other, and the final submission will be a complete interpreter for the `Monkey` programming language.**

Each team will have to create a new private repo, add the following mentor github usernames

- `abhijit424515`
- `ChopstickAyush`
- `k-rt-k`
- `PrrsnCrVS4sr`

as collaborators to your repo, and use the repo to work on this project. The mentors will be monitoring your progress though the commmits (make sure to make reasonably sized commits instead of a lot of changes in a single commit) and will provide feedback on the same.

Whenever a team is ready, they will be given a chance to present their parser and AST whenever they are done with it.

As for the deadline, I am personally not sure how much time this will take, so I am expecting atleast 70% of it should be done by the end of the week (23rd June, 24). We will be continuously checking your progress and will extend the deadline if needed.

---

## Teams

| Name             | Team | Mentors           |
| ---------------- | ---- | ----------------- |
| Malay Kedia      | A    | Abhijit, Sankalan |
| Abhinav Vaishnav | B    | Abhijit, Kartik   |
| Madhava Sriram   | B    | Abhijit, Kartik   |
| Ananya Rao       | C    | Ayush, Kartik     |
| Lakshya Gadhwal  | C    | Ayush, Kartik     |

## Sidenote

Also, I highly encourage you guys to keep asking doubts either in Discord or in the Whatsapp DMs. Lack of communication is the biggest reason for the failure of any project, and we are here to help you guys out with anything, whether it be solving doubts or extending the deadlines.