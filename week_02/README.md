# Week 02

Seeing the responses and progress of the mentees from last week, we have decided to devote an additional week to clarify and understand scanning and parsing.
Accordingly, we will hold a discussion for the same (timing will be in Discord Announcements) to clarify all doubts.

## Assignment

This week's assignment will be to create a parser for YAML, which is very similar to JSON. This time, the assignment is to be done in pairs of 2 (already assigned), and each of the mentee teams will have to make a submission before **Sunday EOD** for this on Github Classroom, **the link to which will be updated here by Thursday EOD**. We will release some testcases by Friday EOD, but the solution will not be released this time, and will only be discussed in a session this Sunday.

Some of the mentees are apparently unable to continue with the current pace, because of which

-   we have shuffled some teams to ensure the current mentees are not at a disadvantage
-   the assignment is to be done in the assigned pairs instead of doing it solo.
-   we are mandating the submission of the above YAML assignment. Since we have uploaded the solutions to the JSON and CSV assignments, this assignment should be on the same level as them, and is only meant to ensure a mentee's participation in this SoC. **Only those mentees who will submit a valid solution to this assignment will be eligible for the SoC certification**.

### YAML Syntax Specification

Since there are many rules in the official YAML syntax, we will only be following the following specification rules (the result will not be a valid YAML file since we are making some contradicting assumptions for this assignment)

- all keys are enclosed in quotes (in YAML, quotes are necessary only if a key has spaces in between, but for simplicity we are always using quotes)
- YAML allows you to use curly braces also for dictionaries, but we will only consider the use of indentation for the same
- Instead of using square brackets to denote a list, we will use a hyphen `-` followed by a tab to denote a list element
- Same as in JSON, `true`, `false` and `null` are in lowercase
- For indentation, YAML uses 2 spaces as a single indent, and using tabs is not valid YAML. However, we will be using the tab character `\t` for indentation in this assignment.
- Other rules, like multiline strings and stuff, are to be ignored for this assignment.

Here is an example

```yaml
-	"1": true
	"2":
	-	"a"
	-	"b"
	"kjsnfjksn":
		"1": "1"
		"2": "2"
		"3": "3"
	"3":
	-	"1": "1"
    	"2": "2"
    	"3": "3"
    -	"1": "1"
    	"2": "2"
    	"3": "3"
```

which is the equivalent of the following JSON 

```json
[
	{
		"1": true,
		"2": [
			"a",
			"b"
		],
		"kjsnfjksn": {
			"1": "1",
			"2": "2",
			"3": "3"
		},
		"3": [
			{
				"1": "1",
				"2": "2",
				"3": "3"
			},
			{
				"1": "1",
				"2": "2",
				"3": "3"
			}
		]
	}
]
```

## Sidenote

Upon contacting the mentees regarding last week's content and assignment progress, most of them had responses ranging from having just started the assignment or not understanding the content to having finished the material but yet to start the assignment. Hardly 1-2 mentees finished the assignment, whose solutions were released about 9-10 days after the assignment release.

We ensured that the content is lucid and easy to interpret and understand. It seems unlikely that a mentee would have significant and fundamental level doubts even after reading through the material. However, there is still a considerable possibility, because of which we urge everyone to ask doubts ASAP. The excuse that you are not understanding the content is not a valid one if you tell it just a few days before the deadline, and that too when a mentor asks you instead of you telling it yourself.

For those of you who did indeed understand the content, we mentors don't have an idea of how much of that is true. Call us paranoid, but we need to ensure our mentees understand and **can implement** an interpreter using their knowledge. This is our primary reason for mandating this week's YAML assignment. This assignment is only meant to be a check on the mentees, and is easy considering it is similar to JSON (solution already released) and that it is to be done in pairs.

The above mentioned doubt and discussion session is meant to clarify all doubts regarding the first week's content. Even if you are fairly confident with the content, we highly recommend all mentees to attend this session.

## Teams

| Name             | Team | Mentors           |
| ---------------- | ---- | ----------------- |
| Arohan Hazarika  | A    | Abhijit, Sankalan |
| Malay Kedia      | A    | Abhijit, Sankalan |
| Abhinav Vaishnav | B    | Kartik, Sankalan  |
| Shravan S        | B    | Kartik, Sankalan  |
| Dion Reji        | C    | Abhijit, Kartik   |
| Madhava Sriram   | C    | Abhijit, Kartik   |
| Ananya Rao       | D    | Ayush, Kartik     |
| Lakshya Gadhwal  | D    | Ayush, Kartik     |
| Deeksha Dhiwakar | E    | Abhijit, Ayush    |
| Kavya Gupta      | E    | Abhijit, Ayush    |
